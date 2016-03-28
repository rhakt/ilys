#include "input.hpp"

namespace rhakt {
namespace ilys {
    
    /* Input */
    std::unordered_map<int, bool> Input::pressed;
    std::unordered_map<int, bool> Input::pulsed;
    std::vector<char> Input::que;
    bool Input::inputStringFlag = false;


} // end of namespace ilys
} // end of namespace rhakt
