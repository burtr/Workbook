#
# various Makefile targets useful for hardhat
#
# https://hardhat.org/hardhat-runner/docs/getting-started
#
# author: bjr
# last-update:
#     10 aug 2024
#     14 aug 2024
#

NETWORK= sepolia
NETWORK= localhost

IGNITION_MODULE= none
TEST_SCRIPT= hello-test.js
DEPOLY_SCRIPT= hello-deploy.js

test:
	npx hardhat run --network ${NETWORK} scripts/${TEST_SCRIPT}

deploy:
	npx hardhat run --network ${NETWORK} scripts/${DEPLOY_SCRIPT}

ignition:
	npx hardhat ignition deploy --network ${NETWORK} ignition/modules/${IGNITION_MODULE}

compile:
	npx hardhat compile
	@echo "You might need to make deploy"

node:
	npx hardhat node 

init:
	npm init
	npm install --save-dev hardhat
	npm hardhat init
	npm install --save-dev @nomicfoundation/hardhat-toolbox
	npm install --save-dev @nomicfoundation/hardhat-ethers ethers
	npm install --save-dev @nomicfoundation/hardhat-ignition-ethers
	-rm addto-hardhat.config.js
	echo "require(\"@nomicfoundation/hardhat-ethers\");" >> addto-hardhat.config.js
	echo "require(\"@nomicfoundation/hardhat-toolbox\");" >> addto-hardhat.config.js
	echo "require(\"@nomicfoundation/hardhat-ignition-ethers\");" >> addto-hardhat.config.js

set-config:
	echo "this will prompt for the Infura Key and your wallet private key"
	npx hardhat vars set INFURA_API_KEY
	npx hardhat vars set SEPOLIA_PRIVATE_KEY
	
