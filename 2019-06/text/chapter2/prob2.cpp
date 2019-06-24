#include <utility>
#include <iostream>
#include <vector>

enum class Weather {
  sunny,
  cloudy,
  rainy
};

using Weather_Ltree = std::pair<Weather, double>;
class WeatherReport {
  private:
    Weather now_weather;
    std::vector<std::vector<double>> weather_parcent{{0.8, 0.2, 0.0}, {0.4, 0.4, 0.2}, {0.2, 0.6, 0.2}};
  public:
    Weather_Ltree next_weather(const Weather&);
    WeatherReport(const Weather&);
};

WeatherReport::WeatherReport(const Weather& now) :now_weather(now){}
Weather_Ltree WeatherReport::next_weather(const Weather& next_weather) {
  int t = 0;
  switch (now_weather) {
    case Weather::sunny:
      t = 0;
      break;
    case Weather::cloudy:
      t = 1;
      break;
    case Weather::rainy:
      t = 2;
      break;
  }
  now_weather = next_weather;

  if (next_weather == Weather::sunny) {
    return std::make_pair(Weather::sunny, weather_parcent[t][0]);
  } else if (next_weather == Weather::cloudy) {
    return std::make_pair(Weather::cloudy, weather_parcent[t][1]);
  } else {
    return std::make_pair(Weather::rainy, weather_parcent[t][2]);
  }
};

double prob_a() {
  WeatherReport DAY(Weather::sunny);
  double sum = 1.0;
  Weather_Ltree t = DAY.next_weather(Weather::cloudy);
  sum *= t.second;
  t = DAY.next_weather(Weather::cloudy);
  sum *= t.second;
  t = DAY.next_weather(Weather::rainy);
  sum *= t.second;
  return sum;
}
int main(int argc, char** argv) {
  std::cout << prob_a() << '\n';
}
