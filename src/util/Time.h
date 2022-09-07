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
  // Methods
  public:
    template<class Int>
    static constexpr std::tuple<Int, unsigned, unsigned> GetDate(Int z) noexcept
    {
      static_assert(std::numeric_limits<unsigned>::digits >= 18, "This algorithm has not been ported to a 16 bit unsigned integer");
      static_assert(std::numeric_limits<Int>::digits >= 20, "This algorithm has not been ported to a 16 bit signed integer");

      z += 719468;
      const Int era = (z >= 0 ? z : z - 146096) / 146097;
      const unsigned doe = static_cast<unsigned>(z - era * 146097);
      const unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
      const Int y = static_cast<Int>(yoe) + era * 400;
      const unsigned doy = doe - (yoe * 365 + yoe / 4 - yoe / 100);
      const unsigned mp = (doy * 5 + 2) / 153;
      const unsigned d = doy - (mp * 153 + 2) / 5 + 1;
      const unsigned m = mp < 10 ? mp + 3 : mp - 9;
      return std::tuple<Int, unsigned, unsigned>(y + (m <= 2), m, d);
    }

    template<typename Duration = std::chrono::hours>
    static void Print(Duration offset = std::chrono::hours(0))
    {
      typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<24>>::type> days;

      std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
      std::chrono::system_clock::duration tp = now.time_since_epoch();

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
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
