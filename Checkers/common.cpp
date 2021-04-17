#include "common.h"

/*Player::DOWN starts*/
Player Common::m_ActivePlayer = Player::DOWN;

void Common::ResetActivePlayer()
{
    m_ActivePlayer = Player::DOWN;
}
