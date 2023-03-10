#include <map>
#include <vector>
#include <string>
#include <string_view>

class Clock {
public:
	Clock();
	~Clock() = default;
	void display();
	void update();
	void run();
private:
	std::map<char, std::vector<std::string_view>> glyphs;
	std::string clock{};
};