////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022 MIT License
////////////////////////////////////////////////////////////////

// Include
#pragma once
#include <chrono>
#include <cstdio>
#include <tuple>

// Time class
class Time
{
  // Properties
  private:
    static inline int timezone = 8;

  // Methods
  public:
    template<class Int>
    static constexpr std::tuple<Int, unsigned int, unsigned int> GetDate(Int z) noexcept
    {
      static_assert(std::numeric_limits<unsigned int>::digits >= 18, "This algorithm has not been ported to a 16 bit unsigned integer");
      static_assert(std::numeric_limits<Int>::digits >= 20, "This algorithm has not been ported to a 16 bit signed integer");

      z += 719468;
      const Int era = (z >= 0 ? z : z - 146096) / 146097;
      const unsigned int doe = static_cast<unsigned int>(z - era * 146097);
      const unsigned int yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
      const Int y = static_cast<Int>(yoe) + era * 400;
      const unsigned int doy = doe - (yoe * 365 + yoe / 4 - yoe / 100);
      const unsigned int mp = (doy * 5 + 2) / 153;
      const unsigned int d = doy - (mp * 153 + 2) / 5 + 1;
      const unsigned int m = mp < 10 ? mp + 3 : mp - 9;
      return std::tuple<Int, unsigned int, unsigned int>(y + (m <= 2), m, d);
    }

    template<typename Duration = std::chrono::hours>
    static void Print(Duration offset = std::chrono::hours(0))
    {
      typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<24>>::type> days;

      std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
      std::chrono::system_clock::duration tp = now.time_since_epoch();

      tp += std::chrono::hours(Time::timezone);
      tp += offset;
      days d = std::chrono::duration_cast<days>(tp);
      tp -= d;
      std::chrono::hours h = std::chrono::duration_cast<std::chrono::hours>(tp);
      tp -= h;
      std::chrono::minutes m = std::chrono::duration_cast<std::chrono::minutes>(tp);
      tp -= m;
      std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(tp);
      tp -= s;

      auto date = Time::GetDate(d.count());
      std::printf("[%04u-%02u-%02u %02lu:%02lu:%02llu.%03llu]", std::get<0>(date), std::get<1>(date), std::get<2>(date), h.count(), m.count(), s.count(), tp / std::chrono::milliseconds(1));
    }

    template<typename Duration = std::chrono::hours>
    static void FilePrint(FILE* file, Duration offset = std::chrono::hours(0))
    {
      typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<24>>::type> days;

      std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
      std::chrono::system_clock::duration tp = now.time_since_epoch();

      tp += std::chrono::hours(Time::timezone);
      tp += offset;
      days d = std::chrono::duration_cast<days>(tp);
      tp -= d;
      std::chrono::hours h = std::chrono::duration_cast<std::chrono::hours>(tp);
      tp -= h;
      std::chrono::minutes m = std::chrono::duration_cast<std::chrono::minutes>(tp);
      tp -= m;
      std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(tp);
      tp -= s;

      auto date = Time::GetDate(d.count());
      std::fprintf(file, "[%04u-%02u-%02u %02lu:%02lu:%02llu.%03llu]", std::get<0>(date), std::get<1>(date), std::get<2>(date), h.count(), m.count(), s.count(), tp / std::chrono::milliseconds(1));
    }
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
