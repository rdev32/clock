#include <sys/ioctl.h>
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <ctime>

std::vector<std::string> get_time()
{
  std::vector<std::string> time;

  std::time_t time_stamp  = std::time(nullptr);
  const char* time_string = std::asctime(std::localtime(&time_stamp));

  std::string hour;
  std::string minute;
  std::string second;

  for(int i = 0; time_string[i] != 0; i++)
  {
    if(time_string[i+2] == ':')
    {
      hour    += time_string[i];
      hour    += time_string[i+1];

      minute  += time_string[i+3];
      minute  += time_string[i+4];

      second  += time_string[i+6];
      second  += time_string[i+7];
      break;
    }
  }

  time.push_back(hour);
  time.push_back(minute);
  time.push_back(second);

  return time;
}

const char* one[5] = 
{
"▄▄▄   ",
"  █   ",
"  █   ",
"  █   ",
"▀▀▀▀▀ ",
};

const char* two[5] = 
{
"▄▄▄▄▄ ",
"    █ ",
"█▀▀▀▀ ",
"█     ",
"▀▀▀▀▀ ",
};

const char* three[5] = 
{
"▄▄▄▄▄ ",
"    █ ",
"▀▀▀▀█ ",
"    █ ",
"▀▀▀▀▀ ",
};

const char* four[5] = 
{
"▄   ▄ ",
"█   █ ",
"▀▀▀▀█ ",
"    █ ",
"    ▀ ",
};

const char* five[5] = 
{
"▄▄▄▄▄ ",
"█     ",
"▀▀▀▀█ ",
"    █ ",
"▀▀▀▀▀ ",
};

const char* six[5] = 
{
"▄▄▄▄▄ ",
"█     ",
"█▀▀▀█ ",
"█   █ ",
"▀▀▀▀▀ ",
};

const char* seven[5] = 
{
"▄▄▄▄▄ ",
"    █ ",
"    █ ",
"    █ ",
"    ▀ ",
};

const char* eight[5] = 
{
"▄▄▄▄▄ ",
"█   █ ",
"█▀▀▀█ ",
"█   █ ",
"▀▀▀▀▀ ",
};

const char* nine[5] = 
{
"▄▄▄▄▄ ",
"█   █ ",
"▀▀▀▀█ ",
"    █ ",
"▀▀▀▀▀ ",
};

const char* zero[5] = 
{
"▄▄▄▄▄ ",
"█   █ ",
"█ ▄▀█ ",
"█▀  █ ",
"▀▀▀▀▀ ",
};

const char* dot[5] = 
{
"   ",
"██ ",
"   ",
"██ ",
"   ",
};

const char* get_number(char value, int index)
{
  if(value == '0')
  {
    return zero[index];
  }
  else if(value == '1')
  {
    return one[index];
  }
  else if(value == '2')
  {
    return two[index];
  }
  else if(value == '3')
  {
    return three[index];
  }
  else if(value == '4')
  {
    return four[index];
  }
  else if(value == '5')
  {
    return five[index];
  }
  else if(value == '6')
  {
    return six[index];
  }
  else if(value == '7')
  {
    return seven[index];
  }
  else if(value == '8')
  {
    return eight[index];
  }
  else if(value == '9')
  {
    return nine[index];
  }

  return 0;
}

int main()
{
  std::vector<std::string> time;

  winsize window_size;

  while(true)
  {
    time = get_time();

    // get window dimensions 
    ioctl(0, TIOCGWINSZ, &window_size);

    // set boundaries 
    std::string left;
    std::string top;

    for(int j = 0; j < (window_size.ws_row - 10) / 2; j++)
      top   += "\n";

    for(int j = 0; j < (window_size.ws_col - 40) / 2; j++)
      left += " ";

    std::system("clear");

    if(top.size() < 1 || left.size() < 5)
    {
      std::cout << "[!] uncapable to display window, limited space" << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      continue;
    }

    // display clock and wait 
    std::cout 
      << top
      << left 
      << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"
      << std::endl;

    for(int i = 0; i < 5; i++)
    {
      std::cout 
      << left 
      << "┃ "
      << get_number(time[0][0], i) 
      << get_number(time[0][1], i) 
      << dot[i] 
      << get_number(time[1][0], i) 
      << get_number(time[1][1], i) 
      << dot[i] 
      << get_number(time[2][0], i) 
      << get_number(time[2][1], i) 
      << " ┃"
      << std::endl;
    }
    std::cout 
      << left
      << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" 
      << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}
