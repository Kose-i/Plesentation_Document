#include <utility>
#include <iostream>
#include <vector>

enum class Weather {
  sunny,
  cloudy,
  rainy
};

class WeatherReport {
  public:
    using LTree = std::pair<WeatherReport, double>;
    virtual std::pair<WeatherReport, double> next_weather(const Weather&);
};

class SunnyDayReport:WeatherReport{
  public:
    virtual std::pair<WeatherReport, double> next_weather(const Weather&);
};
class CloudyDayReport:WeatherReport{
  public:
    virtual std::pair<WeatherReport, double> next_weather(const Weather&);
};
class RainyDayReport:WeatherReport{
  public:
    virtual std::pair<WeatherReport, double> next_weather(const Weather&);
};


std::pair<WeatherReport, double> SunnyDayReport::next_weather(const Weather& t) {
  LTree k;
  if (t == Weather::sunny) {
    SunnyDayReport j;
    k.first = j;
    k.second = 0.8;
    return k;
  } else if (t == Weather::cloudy) {
    CloudyDayReport j;
    k.first = j;
    k.second = 0.2;
    return k;
  } else {
    k.first = RainyDayReport();
    k.second = 0.0;
    return k;
  }
}
std::pair<WeatherReport, double> CloudyDayReport::next_weather(const Weather& t) {
  if (t == Weather::sunny) {
    return std::pair<WeatherReport, double>(SunnyDayReport, 0.4);
  } else if (t == Weather::cloudy) {
    return std::pair<WeatherReport, double>(CloudyDayReport, 0.4);
  } else {
    return std::pair<WeatherReport, double>(RainyDayReport, 0.2);
  }
}
std::pair<WeatherReport, double> RainyDayReport::next_weather(const Weather& t) {
  if (t == Weather::sunny) {
    return std::pair<WeatherReport, double>(SunnyDayReport, 0.2);
  } else if (t == Weather::cloudy) {
    return std::pair<WeatherReport, double>(CloudyDayReport, 0.6);
  } else {
    return std::pair<WeatherReport, double>(RainyDayReport, 0.2);
  }
}


double prob_a() {
  WeatherReport DAY = SunnyDayReport();
  for (auto i = 0;i < 3;++i) {
  }
  return 1.0;
}
int main(int argc, char** argv) {
  std::cout << prob_a();
}
