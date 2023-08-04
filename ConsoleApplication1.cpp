// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <bitcoin/bitcoin.hpp>

// Function to generate a new Bitcoin key pair.
bc::ec_secret generate_key_pair()
{
    bc::data_chunk seed(bc::wallet::ec_secret_size);
    bc::pseudo_random_fill(seed);
    bc::wallet::hd_private key(seed);
    return key.secret();
}

// Function to display the public address of the Bitcoin wallet.
std::string get_public_address(const bc::ec_secret& key)
{
    bc::wallet::payment_address address(key);
    return address.encoded();
}

// Function to send Bitcoin to a recipient address.
bool send_bitcoin(const bc::ec_secret& sender_key,
    const std::string& recipient_address, double amount)
{
    // Connect to the Bitcoin network and broadcast the transaction.
    // For simplicity, we're not implementing the actual blockchain interaction here.
    // Replace this with proper blockchain interaction in a real-world application.
    std::cout << "Sending " << amount << " BTC from " << get_public_address(sender_key) << " to " << recipient_address << "\n";
    return true;
}

int main()
{
    try
    {
        // Generate a new Bitcoin key pair.
        bc::ec_secret my_key = generate_key_pair();

        // Display the public address for receiving Bitcoin.
        std::string my_address = get_public_address(my_key);
        std::cout << "Your Bitcoin Address: " << my_address << "\n";

        // Example: Sending Bitcoin (for demonstration purposes).
        std::string recipient_address;
        double amount_to_send;

        std::cout << "Enter the recipient's Bitcoin address: ";
        std::cin >> recipient_address;

        std::cout << "Enter the amount to send (BTC): ";
        std::cin >> amount_to_send;

        if (amount_to_send <= 0)
        {
            std::cerr << "Invalid amount. Please enter a positive value.\n";
            return 1;
        }

        if (send_bitcoin(my_key, recipient_address, amount_to_send))
        {
            std::cout << "Transaction successful!\n";
        }
        else
        {
            std::cerr << "Transaction failed. Please check the recipient address.\n";
            return 1;
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
