#include <vector>
#include <sstream>
#include <ostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cassert>

struct BigInt {
private:
  using LL = long long int;
  static const LL BASE = 1000000000;
  const int DIG = 9;

public:
  bool neg;
  std::vector<LL> dig;

  BigInt() : neg(false), dig(1, 0ll) {}
  BigInt(const char* str) : BigInt(std::string(str)) {}
  BigInt(const std::string& str) : neg(false) {
	if(str.empty()){
	  dig.assign(1, 0);
	  return;
	}

	int b = 0;
	if(str[b] == '-'){
	  neg = true;
	  ++b;
	}

	LL crt = 0;
	LL p = 1;
	for(int i=(int)(str.size())-1;i>=b;--i,p*=10){
	  if(p == BASE){
		dig.emplace_back(crt);
		crt = 0;
		p = 1;
	  }
	  if(!isdigit(str[i])){
		throw "Non digit is given.";
	  }
	  crt += p * (str[i] - '0');
	}
	if(crt)
	  dig.emplace_back(crt);
	norm();
  }
  BigInt(LL x) : neg(x<0), dig(1, std::abs(x)){
	for(unsigned int i=0;i<dig.size();++i){
	  if(dig[i] >= BASE){
		dig.emplace_back(dig[i] / BASE);
		dig[i] %= BASE;
	  }
	}
  }
  BigInt& operator=(const BigInt& rhs){
	neg = rhs.neg;
	dig = rhs.dig;
	return *this;
  }
  BigInt& operator=(LL x){ return *this = BigInt(x); }
  BigInt& operator=(const char* s){ return *this = BigInt(s); }
  BigInt& operator=(const std::string& s){ return *this = BigInt(s); }

  BigInt operator-() const {
	BigInt res = *this;
	res.neg = !res.neg;
	return res;
  }

  //! ignoring sign
  static int comp(const BigInt& l, const BigInt& r){
	if(l.dig.size() != r.dig.size())
	  return (l.dig.size() < r.dig.size() ? -1: 1);
   
	for(int i=(int)(l.dig.size())-1;i>=0;--i){
	  if(l.dig[i] != r.dig[i])
		return (l.dig[i] < r.dig[i] ? -1: 1);
	}
	return 0;
  }
  //! add ignoring sign
  static void add(BigInt& l, const BigInt& rhs){
	unsigned int i;
	for(i=0;i<rhs.dig.size();++i){
	  if(l.dig.size() <= i){
		l.dig.emplace_back(rhs.dig[i]);
	  }
	  else{
		l.dig[i] += rhs.dig[i];
		if(l.dig[i] >= BASE){
		  l.dig[i] -= BASE;
		  if(l.dig.size() <= i+1)
			l.dig.emplace_back(0);
		  l.dig[i+1]++;
		}
		else if(l.dig[i] < 0){
		  l.dig[i] += BASE;
		  if(l.dig.size() <= i+1)
			l.dig.emplace_back(0);
		  l.dig[i+1]--;
		}
	  }
	}
	for(;i<l.dig.size();++i)
	  if(l.dig[i] >= BASE){
		l.dig[i] -= BASE;
		if(l.dig.size() <= i)
		  l.dig.emplace_back(0);
		l.dig[i+1]++;
	  }
  }
  // subtract ignoring sign, supposed to l >= rhs
  static void sub(BigInt& l, const BigInt& rhs){
	unsigned int i;
	for(i=0;i<rhs.dig.size();++i){
	  l.dig[i] -= rhs.dig[i];
	  if(l.dig[i] < 0){
		l.dig[i] += BASE;
		l.dig[i+1]--;
	  }
	}
	for(;i<l.dig.size();++i)
	  if(l.dig[i] < 0){
		l.dig[i] += BASE;
		l.dig[i+1]--;
	  }
  }
  
  void flip(){
	for(unsigned int i=0;i<dig.size();++i)
	  dig[i] *= -1;
  }
  void norm(){
	while(dig.size() > 1 && dig.back() == 0) dig.pop_back();
	if(dig.size() == 1 && dig[0] == 0) neg = false;
  }
  bool operator==(const BigInt& rhs) const {
	if(neg != rhs.neg || dig.size() != rhs.dig.size()) return false;
	return comp(*this, rhs) == 0;
  }
  bool operator<(const BigInt& rhs) const {
	if(neg != rhs.neg) return neg? true: false;
	if(neg) return comp(rhs, *this) == -1;
	return comp(*this, rhs) == -1;
  }
  bool operator<=(const BigInt& rhs) const {
	if(neg != rhs.neg) return neg? true: false;
	if(neg) return comp(rhs, *this) <= 0;
	return comp(*this, rhs) <= 0;
  }
  bool operator!=(const BigInt& rhs) const { return !(*this == rhs); }
  bool operator>(const BigInt& rhs)  const { return rhs < *this; }
  bool operator>=(const BigInt& rhs) const { return rhs <= *this; }

  BigInt& operator+=(const BigInt& rhs){
	if(!this->neg){
	  if(!rhs.neg)
		add(*this, rhs);
	  else{
		if(comp(*this, rhs) >= 0)
		  sub(*this, rhs);
		else{
		  flip();
		  add(*this, rhs);
		  neg = true;
		}
	  }
	}
	else{
	  if(!rhs.neg){
		if(comp(rhs, *this) >= 0){
		  flip();
		  add(*this, rhs);
		  neg = false;
		}
		else
		  sub(*this, rhs);
	  }
	  else
		add(*this, rhs);
	}

	norm();
	return *this;
  }
  BigInt& operator-=(const BigInt& rhs){ return *this += -rhs; }
  BigInt operator+(const BigInt& rhs) const { BigInt res = *this; return res += rhs; }
  BigInt operator-(const BigInt& rhs) const { BigInt res = *this; return res -= rhs; }

  std::string to_string() const {
	assert(!dig.empty());
	std::string res = neg? "-": "";

	std::ostringstream os;
	os << std::to_string(dig.back());
	for(int i=(int)(dig.size())-2;i>=0;--i){
	  os << std::setfill('0') << std::setw(DIG) << dig[i];
	}
	res += os.str();
	return res;
  }
  // convert long long int anyway
  LL to_ll() const {
	LL res = 0, p = 1;
	for(unsigned int i=0;i<dig.size();++i){
	  res += dig[i] * p;
	  p *= BASE;
	}
	return res * (neg? -1ll: 1);
  }
};
std::ostream& operator<<(std::ostream& os, const BigInt& x){ return os << x.to_string(); }
