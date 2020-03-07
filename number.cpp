#include <iostream>
#include <sstream>
#include <vector>

long long int mod(long long int a, long long int b) {
  long long int m = a % b;
  if (m < 0) {
    return m + b;
  }
  else {
    return m;
  }
}

/// Euclid's algorithm. Returns greatest common divisor of 'a' and 'b'.
long long int gcd(long long int a, long long int b) {
  if (b == 0) {
    return a;
  }
  else {
    return gcd(b, mod(a, b));
  }
}

/// Computes 'x^y(mod N)'.
long long int modexp(long long int x, long long int y, long long int N) {
  if (y == 0) {
    return 1;
  }
  else {
    long long int z = modexp(x, y/2, N);
    if (y % 2 == 0) {
      return mod((z*z), N);
    }
    else {
      return mod(mod(x, N)*mod(z*z, N), N);
    }
  }
}

/// Extended Euclid's algorithm. Returns [x, y, d] such that d = gcd(a,b) and ax + by = d.
std::vector<long long int> ee(long long int a, long long int b) {
  if (b == 0) {
    return {1, 0, a};
  }
  else {
    long long int m = a % b;
    if (m < 0) {
      m += b;
    }
    std::vector<long long int> v = ee(b, m); // v = [x', y', d]
    return {v.at(1), v.at(0)-(a/b)*v.at(1), v.at(2)};
  }
}

/// Returns 'a^-1(mod N)' or reports that no inverse exists.
long long int inverse(long long int a, long long int N) {
  std::vector<long long int> v = ee(a, N);
  if (v.at(2) == 1) {
    return mod(v.at(0), N);
  }
  else {
    return -1;
  }
}

/// Is it prime...
std::string isPrime(long long int N) {
  int tests[] = {2, 3, 5};
  for (unsigned int i = 0; i < 3; i++) {
    if (modexp(tests[i], N-1, N) != 1) { // compute 'a^N-1(mod N)'
      return "no";
    }
  }
  return "yes";
}

/// Follows the RSA algorithm for generating a modulus and public and private exponents.
std::vector<long long int> genKey(long long int p, long long int q) {
  long long int modulus = p*q;
  long long int phi = (p-1)*(q-1);
  int e = 2;
  while (gcd(e, phi) != 1) {
    e++;
  }
  long long int d = inverse(e, phi);
  return {modulus, e, d};
}

int main() {
  std::string data;
  std::string category;
  long long int a, b, x, y, p, q, N;

  while (std::getline(std::cin, data)) {
    std::stringstream ss(data);
    ss >> category;

    if (category == "gcd") {
      ss >> a;
      ss >> b;
      std::cout << gcd(a, b) << std::endl;
    }
    else if (category == "exp") {
      ss >> x;
      ss >> y;
      ss >> N;
      std::cout << modexp(x, y, N) << std::endl;
    }
    else if (category == "inverse") {
      ss >> a;
      ss >> N;
      long long int inv = inverse(a, N);
      if (inv == -1) {
	std::cout << "none" << std::endl;
      }
      else {
	std::cout << inv << std::endl;
      }
    }  
    else if (category == "isprime") {
      ss >> N;
      std::cout << isPrime(N) << std::endl;
    }
    else { // category == "key"
      ss >> p;
      ss >> q;
      std::vector<long long int> v = genKey(p, q);
      std::cout << v.at(0) << " " << v.at(1) << " " << v.at(2) << std::endl;
    }
  }
  
  return 0;
}
