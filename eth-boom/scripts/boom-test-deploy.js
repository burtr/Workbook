// scripts/boom-test-deploy.js
// author: bjr
// last-update: 13 aug 2024

const CONTRACT_CLASS = 'Boom'

async function main () {
  
    const myAccount = (await ethers.getSigners())[0].address;
    const anAccount = (await ethers.getSigners())[1].address;
    
    const ContractClass = await ethers.getContractFactory(CONTRACT_CLASS);
    const contractInstance = await ContractClass.deploy();
    await contractInstance.waitForDeployment();
    const contractAddress = await contractInstance.getAddress();
    console.log(`Deployed ${CONTRACT_CLASS} to ${contractAddress}`);

    const boom = contractInstance ;
    let count = await boom.getCount();
    let accountFunds = await ethers.provider.getBalance(myAccount);
    let contractFunds = await boom.getFunds();

    for (let i=0;i<10;i++) {
        await boom.countDown({value:ethers.parseEther("0.001")});
        count = await boom.getCount();
        accountFunds = (await ethers.provider.getBalance(myAccount));
        contractFunds = await boom.getFunds();
        console.log(`count: ${count}`);
        console.log(`my funds: ${ethers.formatEther(accountFunds)}`);
        console.log(`contract funds: ${ethers.formatEther(contractFunds)}`);
    }
    
    accountFunds = (await ethers.provider.getBalance(anAccount));
    console.log(`other account funds: ${ethers.formatEther(accountFunds)}`);
}

main().then(
    () => process.exit(0)
	).catch(  
	error => {
        console.error(error);
    	process.exit(1);}
	);
