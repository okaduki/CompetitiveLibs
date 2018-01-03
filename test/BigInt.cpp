#include <bits/stdc++.h>
#include <gmp.h>
#include <gtest/gtest.h>
#include "../lib/BigInt.hpp"

using namespace std;

random_device rnd;

int add(int x, int y){
  return x+y;
}

TEST(AddTest, AddGeneral){
  const int MAX = 1e9;
  for(int i=0;i<1000;++i){
	int x = rnd() % MAX;
	int y = rnd() % MAX;
	if(rnd() % 2) x *= -1;
	if(rnd() % 2) y *= -1;

	BigInt bx = x;
	BigInt by = y;
	ASSERT_EQ(x + y, (bx+by).to_ll()) << x << " + " << y;
	
	bx += by;
	ASSERT_EQ(x + y, bx.to_ll()) << x << " += " << y;
  }

  for(int i=0;i<1000;++i){
	long long int x = rnd() % MAX + rnd() % MAX * MAX;
	long long int y = rnd() % MAX + rnd() % MAX * MAX;
	if(rnd() % 2) x *= -1;
	if(rnd() % 2) y *= -1;

	BigInt bx = x;
	BigInt by = y;
	ASSERT_EQ(x + y, (bx+by).to_ll()) << x << " + " << y;
	
	bx += by;
	ASSERT_EQ(x + y, bx.to_ll()) << x << " += " << y;
  }

  char buf[1024];
  for(int i=0;i<1000;++i){
	int digitx = rnd() % 100 + 10;
	int digity = rnd() % 100 + 10;
	string sx, sy;
	if(rnd() % 2) sx += "-";
	if(rnd() % 2) sy += "-";

	sx += to_string(rnd()% MAX+1);
	sy += to_string(rnd()% MAX+1);
	for(int j=0;j<digitx;++j)
	  sx += to_string(rnd()% MAX);
	for(int j=0;j<digity;++j)
	  sy += to_string(rnd()% MAX);

	mpz_t x, y, z;
	mpz_init(x); mpz_init(y); mpz_init(z);
	mpz_set_str(x, sx.c_str(), 10);
	mpz_set_str(y, sy.c_str(), 10);
	mpz_add(z, x, y);
	mpz_get_str(buf, 10, z);

	BigInt bx = sx, by = sy;
	ASSERT_STREQ(buf, (bx+by).to_string().c_str()) << sx << " + " << sy;
	
	bx += by;
	ASSERT_STREQ(buf, bx.to_string().c_str()) << sx << " += " << sy;
  }
}

TEST(AddTest, AddCorner){
  long long int z = 0;
  BigInt bx = z;
  BigInt by = z;
  bx += by;
  ASSERT_EQ(0, bx.to_ll()) << 0 << " += " << 0;

  z = 123456789012345ll;
  bx = z;
  by = -z;
  bx += by;
  ASSERT_EQ(0, bx.to_ll()) << z << " += " << -z;

  z = 123456789012345ll;
  bx = -z;
  by = z;
  bx += by;
  ASSERT_EQ(0, bx.to_ll()) << -z << " += " << z;
}

TEST(SubtractTest, Subtract){
  const long long int MAX = 1e9;
  
  char buf[2048];
  for(int i=0;i<100;++i){
	int digitx = rnd() % 100 + 10;
	int digity = rnd() % 100 + 10;
	string sx, sy;
	if(rnd() % 2) sx += "-";
	if(rnd() % 2) sy += "-";

	sx += to_string(rnd()% MAX+1);
	sy += to_string(rnd()% MAX+1);
	for(int j=0;j<digitx;++j)
	  sx += to_string(rnd()% MAX);
	for(int j=0;j<digity;++j)
	  sy += to_string(rnd()% MAX);

	mpz_t x, y, z;
	mpz_init(x); mpz_init(y); mpz_init(z);
	mpz_set_str(x, sx.c_str(), 10);
	mpz_set_str(y, sy.c_str(), 10);
	mpz_sub(z, x, y);
	mpz_get_str(buf, 10, z);

	BigInt bx = sx, by = sy;
	ASSERT_STREQ(buf, (bx - by).to_string().c_str()) << sx << " - " << sy;

	bx -= by;
	ASSERT_STREQ(buf, bx.to_string().c_str()) << sx << " -= " << sy;
  }
}

TEST(AddTest, MultGeneral){
  const long long int MAX = 1e9;
  for(int i=0;i<1000;++i){
	long long int x = rnd() % MAX;
	long long int y = rnd() % MAX;
	if(rnd() % 2) x *= -1;
	if(rnd() % 2) y *= -1;

	BigInt bx = x;
	BigInt by = y;
	ASSERT_EQ(x * y, (bx * by).to_ll()) << x << " * " << y;
	
	bx *= by;
	ASSERT_EQ(x * y, bx.to_ll()) << x << " *= " << y;
  }

  char buf[1024];
  for(int i=0;i<1000;++i){
	int digitx = rnd() % 50 + 10;
	int digity = rnd() % 50 + 10;
	string sx, sy;
	if(rnd() % 2) sx += "-";
	if(rnd() % 2) sy += "-";

	sx += to_string(rnd()% MAX+1);
	sy += to_string(rnd()% MAX+1);
	for(int j=0;j<digitx;++j)
	  sx += to_string(rnd()% MAX);
	for(int j=0;j<digity;++j)
	  sy += to_string(rnd()% MAX);

	mpz_t x, y, z;
	mpz_init(x); mpz_init(y); mpz_init(z);
	mpz_set_str(x, sx.c_str(), 10);
	mpz_set_str(y, sy.c_str(), 10);
	mpz_mul(z, x, y);
	mpz_get_str(buf, 10, z);

	BigInt bx = sx, by = sy;
	ASSERT_STREQ(buf, (bx * by).to_string().c_str()) << sx << " * " << sy;
	
	bx *= by;
	ASSERT_STREQ(buf, bx.to_string().c_str()) << sx << " *= " << sy;
  }
}

int main(int argc, char** argv){
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
