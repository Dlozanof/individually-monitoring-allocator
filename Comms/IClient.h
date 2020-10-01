#ifndef DDAD541D_77E6_466C_BA33_E5DFC5A3EBA0
#define DDAD541D_77E6_466C_BA33_E5DFC5A3EBA0
#include <string>

class IClient
{
        virtual void NewData(std::string id, bool data, int local, int global) = 0;
};
#endif /* DDAD541D_77E6_466C_BA33_E5DFC5A3EBA0 */
