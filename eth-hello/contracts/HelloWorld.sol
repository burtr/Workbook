// contracts/HelloWorld.sol
// SPDX-License-Identifier: UNLICENSED
//  ^ means 0.9 etc also acceptable (~ means 0.8.25 also acceptable)
pragma solidity ^0.8.24;

// Uncomment this line to use console.log
// import "hardhat/console.sol";


contract HelloWorld {

        string private _greeting = "Hello World!" ;
        address private _owner ;

        constructor () {
                _owner = msg.sender ;
        }

        modifier onlyOwner() {
                require (
                        msg.sender == _owner, "Ownable: caller is not the owner"
                ) ;
                _ ;
        }

        function getGreeting() external view returns(string memory) {
                return _greeting ;
        }

        function setGreeting(string calldata greeting) external onlyOwner {
                _greeting = greeting ;
        } 

        function owner() public view returns(address) {
                return _owner ;
        }

}


