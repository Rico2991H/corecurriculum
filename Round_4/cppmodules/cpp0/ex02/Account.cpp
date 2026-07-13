/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:42:20 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/02 14:59:15 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

Account::Account( int initial_deposit )
{
		_nbAccounts++;
		_accountIndex = _nbAccounts - 1;
		_amount = initial_deposit;
		_totalAmount += initial_deposit;
		_nbDeposits = 0;
		_nbWithdrawals = 0;
		_displayTimestamp();
		std::cout << " ";
		std::cout << "index:" << _accountIndex << ";";
		std::cout << "amount:" << _amount << ";";
		std::cout << "created" << std::endl;
	
}

Account::~Account( void )
{
	_displayTimestamp();
	std::cout << " ";
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "amount:" << _amount << ";";
	std::cout << "closed" << std::endl;
}

int		Account::getNbAccounts( void ) { return _nbAccounts; }
int 	Account::getTotalAmount( void ) { return _totalAmount; }
int 	Account::getNbDeposits( void ) { return _totalNbDeposits; }
int 	Account::getNbWithdrawals( void ) { return _totalNbWithdrawals; }

void	Account::_displayTimestamp( void )
{
	char Buffer[80];
	time_t timestamp = time(NULL);
	tm* local_time = localtime(&timestamp);
	strftime (Buffer, 80, "[%G%m%d_%H%M%S]", local_time);
	std::cout << Buffer;
}

void 	Account::displayAccountsInfos( void ) 
{
	_displayTimestamp();
	std::cout << " ";
	std::cout << "accounts:" << getNbAccounts();
	std::cout << ";";
	std::cout << "total:" << getTotalAmount();
	std::cout << ";";
	std::cout << "deposits:" << _totalNbDeposits;
	std::cout << ";";
	std::cout << "withdrawals:" << _totalNbWithdrawals << std::endl;
	
}

void	Account::makeDeposit( int deposit )
{
	_displayTimestamp();
	std::cout << " ";
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "p_amount:" << _amount << ";";
	std::cout << "deposit:" << deposit << ";";
	_amount += deposit;
	_totalAmount += deposit;
	std::cout << "amount:" << _amount << ";";
	_nbDeposits++;
	std::cout << "nb_deposits:" << _nbDeposits << std::endl;
	_totalNbDeposits++;
}

bool	Account::makeWithdrawal( int withdrawal )
{
	_displayTimestamp();
	std::cout << " ";
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "p_amount:" << _amount << ";";
	if (_amount >= withdrawal)
	{
		std::cout << "withdrawal:" << withdrawal << ";";
		_amount -= withdrawal;
		_totalAmount -= withdrawal;
		std::cout << "amount:" << _amount << ";";
		_nbWithdrawals++;
		_totalNbWithdrawals++;
		std::cout << "nb_withdrawals:" << _nbWithdrawals << std::endl;
		return(true);
	}	
	else
	{
		std::cout << "withdrawal:" << "refused" << std::endl;
		return(false);
	}
}

int		Account::checkAmount( void ) const
{
	std:: cout << _amount;
	return(_amount);
}
	
void	Account::displayStatus( void ) const
{
	_displayTimestamp();
	std::cout << " ";
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "amount:" << _amount << ";";
	std::cout << "deposits:" << _nbDeposits << ";";
	std::cout << "withdrawals:" << _nbWithdrawals;
	std::cout << std::endl;
}

void	show_accounts(Account** Accounts, int n)
{
	int	i = 0;
	Account::displayAccountsInfos();
	while (i < n)
	{
		Accounts[i]->displayStatus();
		i++;
	}
	
}
void	make_withdrawals(Account** Accounts, int n, int *draw)
{
	int	i = 0;
	while (i < n)
	{
		Accounts[i]->makeWithdrawal(draw[i]);
		i++;
	}
}

void	make_deposits(Account** Accounts, int n, int *dep)
{
	int i = 0;
	while (i < n)
	{
		Accounts[i]->makeDeposit(dep[i]);
		i++;
	}	
}

/*int		main()
{
	int	i = 0;
	Account*	NewAccount[8] = 
	{
		new Account(42), 
		new Account(54), 
		new Account(957), 
		new Account(432), 
		new Account(1234), 
		new Account(0), 
		new Account(754), 
		new Account(16576)
	};
	int	dep[] = {5, 765, 564, 2, 87, 23, 9, 20};
	int	draw[] = {48, 34, 657, 4, 76, 24, 657, 7654};
	int	n = NewAccount[i]->getNbAccounts();
	show_accounts(NewAccount, n);
	make_deposits(NewAccount, n, dep);
	show_accounts(NewAccount, n);
	make_withdrawals(NewAccount, n, draw);
	show_accounts(NewAccount, n);
	for(int i = 0; i < n; i++)
		delete NewAccount[i];
	return (0);
}*/
