#include "Commands.hpp"
#include <limits>

int isIntOrDigit(const std::string str) {
  std::regex digits("\\d+");
  std::regex letters("[A-Z]+");

  if (std::regex_match(str, digits))
    return std::stoi(str);
  else if (std::regex_match(str, letters))
    return -1;
  else
    return 0;
}

void area(std::vector<kabalin::Polygon> &data, std::string &str) {
  auto sum = [](double value, const kabalin::Polygon &pl, const int rem,
                int divisor) {
    double res = value;
    if (pl.points.size() % divisor == static_cast<size_t>(rem) || rem == -1)
      res += pl.area();
    return res;
  };

  if (isIntOrDigit(str) == -1) {
    if (str == "EVEN") {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                                   std::bind(sum, std::placeholders::_1,
                                             std::placeholders::_2, 0, 2))
                << std::endl;
    }

    else if (str == "ODD") {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                                   std::bind(sum, std::placeholders::_1,
                                             std::placeholders::_2, 1, 2))
                << std::endl;
    }

    else if (str == "MEAN" && data.size() != 0) {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                                   std::bind(sum, std::placeholders::_1,
                                             std::placeholders::_2, -1, 2)) /
                       data.size()
                << std::endl;
    }

    else
      throw ERROR_OF_COMMAND;
  } else if (isIntOrDigit(str) > 2) {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                                 std::bind(sum, std::placeholders::_1,
                                           std::placeholders::_2,
                                           isIntOrDigit(str),
                                           std::numeric_limits<int>::max()))
              << std::endl;
  } else
    throw ERROR_OF_COMMAND;
}

void max(std::vector<kabalin::Polygon> &data, std::string &str) {
  if (data.empty())
    throw ERROR_OF_COMMAND;
  else {
    if (str == "AREA") {
      auto maxArea = *std::max_element(
          data.begin(), data.end(),
          [](const kabalin::Polygon &pl1, const kabalin::Polygon &pl2) {
            return pl1.area() < pl2.area();
          });
      std::cout << maxArea.area() << std::endl;
    } else if (str == "VERTEXES") {
      auto maxVertexes = *std::max_element(
          data.begin(), data.end(),
          [](const kabalin::Polygon &pl1, const kabalin::Polygon &pl2) {
            return pl1.points.size() < pl2.points.size();
          });
      std::cout << maxVertexes.points.size() << std::endl;
    } else
      throw ERROR_OF_COMMAND;
  }
}

void min(std::vector<kabalin::Polygon> &data, std::string &str) {
  if (data.empty())
    throw ERROR_OF_COMMAND;
  else {
    if (str == "AREA") {
      auto maxArea = *std::min_element(
          data.begin(), data.end(),
          [](const kabalin::Polygon &pl1, const kabalin::Polygon &pl2) {
            return pl1.area() < pl2.area();
          });
      std::cout << maxArea.area() << std::endl;
    } else if (str == "VERTEXES") {
      auto maxVertexes = *std::min_element(
          data.begin(), data.end(),
          [](const kabalin::Polygon &pl1, const kabalin::Polygon &pl2) {
            return pl1.points.size() < pl2.points.size();
          });
      std::cout << maxVertexes.points.size() << std::endl;
    } else
      throw ERROR_OF_COMMAND;
  }
}

void count(std::vector<kabalin::Polygon> &data, std::string &str) {
  auto cnt = [](kabalin::Polygon &el, const int rem, int divisor) {
    return el.points.size() % divisor == static_cast<size_t>(rem) || rem == -1;
  };

  if (isIntOrDigit(str) == -1) {
    if (str == "EVEN") {
      std::cout << std::count_if(data.begin(), data.end(),
                                 std::bind(cnt, std::placeholders::_1, 0, 2))
                << std::endl;
    } else if (str == "ODD") {
      std::cout << std::count_if(data.begin(), data.end(),
                                 std::bind(cnt, std::placeholders::_1, 1, 2))
                << std::endl;
    } else
      throw ERROR_OF_COMMAND;
  }

  else if (isIntOrDigit(str) > 2) {
    std::cout << std::count_if(data.begin(), data.end(),
                               std::bind(cnt, std::placeholders::_1,
                                         isIntOrDigit(str),
                                         std::numeric_limits<int>::max()))
              << std::endl;
  } else
    throw ERROR_OF_COMMAND;
}

void same(std::vector<kabalin::Polygon> &data) {
  if (data.empty())
    throw ERROR_OF_COMMAND;

  kabalin::Polygon newPoly;

  std::cin >> newPoly;
  int el = std::cin.get();

  while (el != int('\n') && el != std::cin.eof()) {
    if (!isspace(el)) {
      std::cin.setstate(std::istream::failbit);
      break;
    }
    el = std::cin.get();
  }
  if (std::cin.fail()) {
    std::cin.clear();
    throw ERROR_OF_COMMAND;
  }

  auto cnt = [&newPoly](kabalin::Polygon el) { return newPoly.isSame(el); };
  std::cout << std::count_if(data.begin(), data.end(), cnt) << std::endl;
}

void lessArea(std::vector<kabalin::Polygon> &data) {
  if (data.empty())
    throw ERROR_OF_COMMAND;

  kabalin::Polygon newPoly;

  std::cin >> newPoly;
  int el = std::cin.get();

  while (el != int('\n') && el != std::cin.eof()) {
    if (!isspace(el)) {
      std::cin.setstate(std::istream::failbit);
      break;
    }
    el = std::cin.get();
  }
  if (std::cin.fail()) {
    std::cin.clear();
    throw ERROR_OF_COMMAND;
  }

  auto cnt = [&newPoly](kabalin::Polygon el) {
    return el.area() < newPoly.area();
  };
  std::cout << std::count_if(data.begin(), data.end(), cnt) << std::endl;
}
