#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <cmath>
#include <exception>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;

namespace id3 {

class InvalidSumOfProbabilitiesException : public std::exception {
 private:
  std::string m_strErrMsg;

 public:
  explicit InvalidSumOfProbabilitiesException(const std::string& strErrMsg)
      : m_strErrMsg{strErrMsg} {}
  virtual const char* what() const noexcept override {
    return m_strErrMsg.c_str();
  }
};

class InvalidNumberOfEntriesException : public std::exception {
 private:
  std::string m_strErrMsg;

 public:
  explicit InvalidNumberOfEntriesException(const std::string& strErrMsg)
      : m_strErrMsg{strErrMsg} {}
  virtual const char* what() const noexcept override {
    return m_strErrMsg.c_str();
  }
};

using Count = int;
using Entropy = double;

/**
 * @brief Calculate entropy for a given attribute
 *
 * @param probabilities - P(class 0) = probabilites[0], P(class 1) =
 * probabilities[1] and so on...
 *
 * The sum of the vector should be 1
 *
 * For example, if we have 3 shapes for an apple, and shape 0 has probability of
 * 0.5, then probabilites[0] = 0.5 The other 2 could be probabilites[1] = 0.3
 * and probabilites[2] = 0.2
 *
 * @return the entropy
 *
 * @throw InvalidVectorOfProbabilitiesException if the sum of the probabilities
 * is not 1
 */
Entropy calculateEntropy(const vector<double>& probabilities) {
  double sumOfProbabilites = 0;
  for (auto probability : probabilities) {
    sumOfProbabilites += probability;
  }

  if (sumOfProbabilites != 1) {
    throw InvalidSumOfProbabilitiesException(
        "Sum of all probabilites is not 1!");
  }

  Entropy entropy = 0;
  for (auto probability : probabilities) {
    entropy -= probability * log2(probability);
  }
  return entropy;
}

// clang-format off
/**
 * @brief calculate average information entropy for a given attribute
 *
 * For example, let's say we have an attribute 'outlook' which has 3 values - rainy,
 * overcast and sunny.
 * The average information entropy I(outlook) =
 * (number of entries with rainy outlook / total number of entries) * entropy(Outlook = rainy) +
 * (number of entries with overcast outlook / total number of entries) * entropy(Outlook = overcast) +
 * (number of entries with sunny outlook / total number of entries) * entropy(Outlook = sunny)
 *
 * @return the average information entropy
 * @throw InvalidNumberOfEntriesException if number of entries for specific attribute value is higher than
 * the total number of entries
 */
// clang-format on
Entropy calculateAverageInformationEntropy(
    int totalNumberOfEntries,
    const vector<pair<Count, Entropy>>& attributeAndItsEntropyPair) {
  Entropy averageInformationEntropy = 0;
  for (const auto& [count, entropy] : attributeAndItsEntropyPair) {
    if (count > totalNumberOfEntries) {
      stringstream error;
      error << "The number of entries for specific attribute value (" << count
            << ") cannot be higher than the total number of entries ("
            << totalNumberOfEntries << ").";
      throw InvalidNumberOfEntriesException(error.str());
    }

    averageInformationEntropy +=
        (static_cast<double>(count) / totalNumberOfEntries) * entropy;
  }
  return averageInformationEntropy;
}

}  // namespace id3

#endif