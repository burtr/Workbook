// scripts/hello-test.js
// author: bjr
// last-update: 9 aug 2024
//     14 aug 2024

// file out this value from the output of the deploy script
const CONTRACT_ADDRESS = "0xd753c12650c280383Ce873Cc3a898F6f53973d16";

async function main () {
  const deployedContractAddress = CONTRACT_ADDRESS;
  const HelloWorld = await ethers.getContractFactory('HelloWorld');
  const helloWorld = await HelloWorld.attach(deployedContractAddress);

  var owner = helloWorld.getOwner();
  var greeting = await helloWorld.getGreeting();
  console.log(`owner: ${owner}\ngreeting:${greeting}`);
  
  await helloWorld.setGreeting('Hello Moon!');
  greeting = await helloWorld.getGreeting();
  console.log(`greeting:${greeting}`);  
}

main()
  .then(() => process.exit(0))
  .catch(error => {
    console.error(error);
    process.exit(1);
  });


