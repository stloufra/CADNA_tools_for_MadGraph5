//
// Created by Frantisek Stloukal on 21.11.2025.
//

#ifndef CPPPROCESS_STANDALONE_REPAIR_MOMENTA_H
#define CPPPROCESS_STANDALONE_REPAIR_MOMENTA_H
#include <vector>
#include <cmath>
#include <iostream>
#include <array>
#include <algorithm>
#include <unistd.h>

#include "typeTraits.h"

namespace momenta_reparator
{
    using std::sqrt;
    using std::fabs;
    using std::max;
    using std::min;
    using std::sqrt;
    using std::log;
    using std::tanh;

    struct P4 {
        fptypemomenta E, px, py, pz;
    };

    struct P3
    {

        fptypemomenta v[3];

        P3() = default;

        P3(fptypemomenta x, fptypemomenta y, fptypemomenta z) : v{x,y,z} {}

        fptypemomenta& operator[](int i) { return v[i]; }

        const fptypemomenta& operator[](int i) const { return v[i]; }
    };

 const static fptypemomenta EPS =
     std::is_same_v<fptypemomenta, float>  ? fptypemomenta(1e-7) :
     std::is_same_v<fptypemomenta, double> ? fptypemomenta(1e-15) :
     fptypemomenta(0);

    // Basic vector utilities

    inline fptypemomenta norm3(const fptypemomenta& x, const fptypemomenta& y, const fptypemomenta& z){
        return sqrt(x*x + y*y + z*z);
    }

    inline fptypemomenta dot3(const P3& a, const P3& b){
        return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
    }

    inline P3 to3(const P4& p){
        return {p.px, p.py, p.pz};
    }

    inline P3 minus(const P3& a)
    {
        return {-a[0], -a[1], -a[2]};
    }

    inline P3 normalize(const P3& v){
        fptypemomenta n = norm3(v[0], v[1], v[2]);
        if(n < EPS) return {0.f,0.f,1.f};
        return {v[0]/n, v[1]/n, v[2]/n};
    }

    inline P3 cross3(const P3& a,
                                        const P3& b){
        return {
            (a[1]*b[2] - a[2]*b[1]),
            (a[2]*b[0] - a[0]*b[2]),
            (a[0]*b[1] - a[1]*b[0])
        };
    }

    // Lorentz boost
    P4 lorentz_boost(const P4& p, const P3& beta){
        fptypemomenta b2 = dot3(beta, beta);
        if(b2 >= 1.0f) throw std::runtime_error("Boost over speed of light requested");

        fptypemomenta gamma = 1.0f / sqrt(1.0f - b2);

        auto v = to3(p);
        fptypemomenta bp = dot3(beta, v);

        fptypemomenta Eprime = gamma * (p.E - bp);

        P3 pprime = {
            v[0] + ((gamma - 1.0)/b2)*bp*beta[0] - gamma*p.E*beta[0],
            v[1] + ((gamma - 1.0)/b2)*bp*beta[1] - gamma*p.E*beta[1],
            v[2] + ((gamma - 1.0)/b2)*bp*beta[2] - gamma*p.E*beta[2]
        };

        return {Eprime, pprime[0], pprime[1], pprime[2]};
    }

    // Collinearity test
    fptypemomenta collinearity(const P4& a, const P4& b){
        auto va = to3(a);
        auto vb = to3(b);

        fptypemomenta na = norm3(va[0], va[1], va[2]);
        fptypemomenta nb = norm3(vb[0], vb[1], vb[2]);

        if(na < EPS || nb < EPS) return 1.0;

        return fabs(dot3(va, vb)) / (na * nb);
    }

    // Find perpendicular unit vector
    P3 perpendicular_unit(const P3& n){
        P3 tmp =
            (fabs(n[0]) < 0.9 ? P3{1,0,0} : P3{0,1,0});
        auto perp = cross3(n, tmp);
        return normalize(perp);
    }

    // Main repair function
    std::vector<P4> repair_event(
        std::vector<P4> particles,
        bool& rep,
        fptypemomenta coll_cut = 0.995,
        fptypemomenta soft_ratio = 50.0
    ){
        const size_t N = particles.size();

        for(size_t i = 0; i < N; ++i){
            for(size_t j = i+1; j < N; ++j){
                if (i== 0 && j == 1) continue;
                const auto &pi = particles[i];
                const auto &pj = particles[j];

                // ---- Compute metrics ----
                fptypemomenta coll = collinearity(pi, pj);
                fptypemomenta Eratio = std::max(pi.E, pj.E) / std::min(pi.E, pj.E);

                bool is_collinear = coll > coll_cut;
                bool is_soft = Eratio > soft_ratio;

                if(!is_collinear && !is_soft) continue;

                auto vi = to3(pi);
                auto vj = to3(pj);

                auto ni = normalize(vi);
                auto nj = normalize(vj);

                // Common axis
                auto axis = normalize({
                    ni[0] + nj[0],
                    ni[1] + nj[1],
                    ni[2] + nj[2]
                });

                P3 beta = {0,0,0};

                if(is_collinear){
                    // Transverse boost (open angle)
                    auto perp = axis; // perpendicular_unit(axis);
                    //std::cout << dot3(axis, perp) << std::endl;
                    fptypemomenta beta_mag = 0.95f; // safe fixed value (TODO:can be adaptive)
                    beta = { beta_mag*perp[0], beta_mag*perp[1], beta_mag*perp[2] };

                    //std::cout << "[COLLINEAR FIX] Pair ("<<i<<","<<j<<") C="<<coll<<"\n";
                }

                else if(is_soft){
                    // Longitudinal boost (energy balancing)
                    bool i_soft = pi.E < pj.E;

                    // Boost direction: along axis
                    auto boost_dir = axis;
                    if(i_soft) {
                        // boost along particle j gives energy to i
                        boost_dir = {axis[0], axis[1], axis[2]};
                    } else {
                        boost_dir = {-axis[0], -axis[1], -axis[2]};
                    }

                    fptypemomenta beta_mag = 0.2f * tanh(log(Eratio)/2.0);
                    beta = {
                        beta_mag * boost_dir[0],
                        beta_mag * boost_dir[1],
                        beta_mag * boost_dir[2]
                    };

                    //std::cout << "[SOFT FIX] Pair ("<<i<<","<<j<<") Ratio="<<Eratio<<"\n";
                }

                // Apply boost globally
                for(auto &p : particles){
                    p = lorentz_boost(p, beta);
                }

                rep = true;
                return particles; // stop after first correction (TODO: extended later)
            }
        }
        rep = false;
        return particles;
    }

    void BoostMomenta(auto& hstMomenta, const int nevt, fptypemomenta coll_cut = 0.995, fptypemomenta soft_ratio = 50.0)
    {
        for (unsigned int ievt = 0; ievt < nevt; ++ievt) // Loop over all events in this iteration
        {
            std::vector<P4> particles(CPPProcess::npar);
            for (int ipar = 0; ipar < CPPProcess::npar; ipar++)
            {
                particles[ipar].E = MemoryAccessMomenta::ieventAccessIp4IparConst(hstMomenta.data(), ievt, 0, ipar);
                particles[ipar].px = MemoryAccessMomenta::ieventAccessIp4IparConst(hstMomenta.data(), ievt, 1, ipar);
                particles[ipar].py = MemoryAccessMomenta::ieventAccessIp4IparConst(hstMomenta.data(), ievt, 2, ipar);
                particles[ipar].pz = MemoryAccessMomenta::ieventAccessIp4IparConst(hstMomenta.data(), ievt, 3, ipar);

            }

            //std::cout << "Event " << ievt << std::endl;
            bool repair = true;
            int i = 0;
            while (repair && i < 3)
            {
                particles = repair_event(particles, repair, coll_cut, soft_ratio);
                i++;
            }

            for (int ipar = 0; ipar < CPPProcess::npar; ipar++)
            {
                MemoryAccessMomenta::ieventAccessIp4Ipar(hstMomenta.data(), ievt, 0, ipar) = (double)particles[ipar].E;
                MemoryAccessMomenta::ieventAccessIp4Ipar(hstMomenta.data(), ievt, 1, ipar) = (double)particles[ipar].px;
                MemoryAccessMomenta::ieventAccessIp4Ipar(hstMomenta.data(), ievt, 2, ipar) = (double)particles[ipar].py;
                MemoryAccessMomenta::ieventAccessIp4Ipar(hstMomenta.data(), ievt, 3, ipar) = (double)particles[ipar].pz;
            }
        }
    }
}
#endif //CPPPROCESS_STANDALONE_REPAIR_MOMENTA_H