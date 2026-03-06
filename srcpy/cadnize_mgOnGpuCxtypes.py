#file from argument:
import sys
if len(sys.argv) > 1:
    fileName = sys.argv[1]
else:
    exit("No file name given")
#move every "$(LIBFLAGS)" to the end of the line in the file test.mak
f = open(fileName, "r")

operatorString = """
  //CADNA operator overload
  template <typename T>
  constexpr bool is_special_fp_v =
      std::is_same_v<T, double_st> || std::is_same_v<T, float_st>;
  
  template <typename FP, typename FP2,
            std::enable_if_t<is_special_fp_v<FP> || is_special_fp_v<FP2>, int> = 0>
  inline constexpr auto
  operator+(const cxsmpl<FP>& a, const cxsmpl<FP2>& b)
  {
      if constexpr (is_special_fp_v<FP>)
      {
          cxsmpl<FP> b_temp = b;
          return cxsmpl<FP>(a.real() + b_temp.real(), a.imag() + b_temp.imag());
      }
      else
      {
          cxsmpl<FP2> a_temp = a;
          return cxsmpl<FP2>(a_temp.real() + b.real(), a_temp.imag() + b.imag());
      }
  }
  
  template <typename FP, typename FP2,
            std::enable_if_t<is_special_fp_v<FP> || is_special_fp_v<FP2>, int> = 0>
  inline constexpr auto
  operator-(const cxsmpl<FP>& a, const cxsmpl<FP2>& b)
  {
      if constexpr (is_special_fp_v<FP>)
      {
          cxsmpl<FP> b_temp = b;
          return cxsmpl<FP>(a.real() - b_temp.real(), a.imag() - b_temp.imag());
      }
      else
      {
          cxsmpl<FP2> a_temp = a;
          return cxsmpl<FP2>(a_temp.real() - b.real(), a_temp.imag() - b.imag());
      }
  }
  
  template <typename FP, typename FP2,
            std::enable_if_t<is_special_fp_v<FP> || is_special_fp_v<FP2>, int> = 0>
  inline constexpr auto
  operator*(const cxsmpl<FP>& a, const cxsmpl<FP2>& b)
  {
      if constexpr (is_special_fp_v<FP>)
      {
          cxsmpl<FP> b_temp = b;
          return cxsmpl<FP>(a.real() * b_temp.real() - a.imag() * b_temp.imag(),
                            a.imag() * b_temp.real() + a.real() * b_temp.imag());
      }
      else
      {
          cxsmpl<FP2> a_temp = a;
          return cxsmpl<FP2>(a_temp.real() * b.real() - a_temp.imag() * b.imag(),
                             a_temp.imag() * b.real() + a_temp.real() * b.imag());
      }
  }
  
  template <typename FP, typename FP2,
            std::enable_if_t<is_special_fp_v<FP> || is_special_fp_v<FP2>, int> = 0>
  inline constexpr auto
  operator/(const cxsmpl<FP>& a, const cxsmpl<FP2>& b)
  {
      if constexpr (is_special_fp_v<FP>)
      {
          cxsmpl<FP> b_temp = b;
          FP bnorm = b_temp.real() * b_temp.real() + b_temp.imag() * b_temp.imag();
          return cxsmpl<FP>((a.real() * b_temp.real() + a.imag() * b_temp.imag()) / bnorm,
                            (a.imag() * b_temp.real() - a.real() * b_temp.imag()) / bnorm);
      }
      else
      {
          cxsmpl<FP2> a_temp = a;
          FP2 bnorm = b.real() * b.real() + b.imag() * b.imag();
          return cxsmpl<FP2>((a_temp.real() * b.real() + a_temp.imag() * b.imag()) / bnorm,
                             (a_temp.imag() * b.real() - a_temp.real() * b.imag()) / bnorm);
      }
  }

template < typename FP2,
            std::enable_if_t< is_special_fp_v<FP2>, int> = 0>
  inline constexpr auto
  operator*(const double& a, const cxsmpl<FP2>& b)
  {
      return cxsmpl<FP2>(a,0. )*b;
  }

  template < typename FP2,
            std::enable_if_t< is_special_fp_v<FP2>, int> = 0>
  inline constexpr auto
  operator*( const cxsmpl<FP2>& a, const double& b)
  {
    return a*cxsmpl<FP2>(b,0.);
  }

"""

#read lines
lines = f.readlines()
f.close()
changes = 0

i=0
operatorOverload = False
for idx, l in enumerate(lines):
    if "CADNA operator overload" in l:
       operatorOverload = True
    if "template<typename FP2> __host__ __device__ constexpr operator cxsmpl<FP2>() const { return cxsmpl<FP2>( m_real, m_imag ); }" in l:
       lines[idx] = l.replace("> __host__", "> explicit __host__")
       changes += 1


if not operatorOverload:
    for l in lines:
        if "operator/( const cxsmpl<FP>& a, const FP& b )" in l:
            lines.insert(i+4, operatorString)
            changes += 1
            break

        i=i+1

new_lines = []
i = 0

while i < len(lines):
    l = lines[i]

    if (
    "inline __host__ __device__ constexpr cxsmpl<float>" in l
    and i + 1 < len(lines)
    and "operator*" in lines[i + 1]
    and "cxsmpl<float>" in lines[i + 1]
    and "double" in lines[i + 1]
    ):
        changes += 1
        # skip until end of function
        while i < len(lines) and "}" not in lines[i]:
            i += 1
        i += 1  # skip closing brace
        continue

    new_lines.append(l)
    i += 1

lines = new_lines

print(f"Changes in: {fileName:<30}\t{changes}")

from shutil import move, copymode
from os import fdopen, remove

#replace old file with new file
tempfileName = fileName+"_temp"
f = open(tempfileName, "w")
f.writelines(lines)
f.close()

#Copy the file permissions from the old file to the new file
copymode(fileName, tempfileName)
#Remove original file
remove(fileName)
#Move new file
move(tempfileName, fileName)
