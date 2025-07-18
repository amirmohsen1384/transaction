#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "general.h"
#include "accounts/loanaccount.h"
#include "accounts/depositaccount.h"
#include "accounts/transactionaccount.h"

Account* loadFromKey(const Key &identifier);

#endif // ACCOUNT_H
