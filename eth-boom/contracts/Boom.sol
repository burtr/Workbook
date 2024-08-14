// contracts/Boom.sol

// author: bjr
// last-update: 9 aug 2024

// SPDX-License-Identifier: UNLICENSED
//  ^ means 0.9 etc also acceptable (~ means 0.8.25 also acceptable)
pragma solidity ^0.8.24;

import "hardhat/console.sol";

contract Boom {

    uint256 public count;
	address payable public owner;
	
	uint256 constant public TOP_COUNT = 10;
	uint256 constant public STAKE = (1 ether)/1000;
	
	event BoomEvent(address indexed boomer, address indexed owner, string message);
	
	constructor() {
        owner = payable(msg.sender);
        count = 10;
    }

    function getCount() external view returns (uint256) {
        return count;
    }
    
    function getFunds() external view returns (uint256) {
    	return address(this).balance;
    }

    // Function to increment count by 1
    function countDown() external payable returns (uint256) {
    	uint256 stake = msg.value; 
    	require(stake>=STAKE,'Stake 0.001 ETH');
    	uint256 d = stake-STAKE; 
    	if (d>0) {
    		(bool success,) = (msg.sender).call{value: d}("");
    		require(success, "Failed to reimburse sender Ether");
    	}    
        count -= 1;
        if (count<=0) {
        	uint256 t = address(this).balance;
        	(bool success,) = owner.call{value: t}("");
        	require(success, "Failed to send boomed Ether");
        	count = 10 ;
        	// event
        	emit BoomEvent(address(this), owner, "Boom!");
        }
        return 0;
    }

}

// npx hardhat compile
// npx hardhat ignition deploy ./ignition/modules/boom.js --network localhost
// npx hardhat run --network localhost scripts/deploy.js

// await ethers.provider.getLogs({})  
