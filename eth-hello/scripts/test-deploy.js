// scripts/deploy.js
async function main () {
  // We get the contract to deploy
  const HelloWorld = await ethers.getContractFactory('HelloWorld');
  console.log('Deploying HelloWorld ...');
  const hello_world = await HelloWorld.deploy();
  await hello_world.waitForDeployment();
  console.log('HelloWorld deployed to:', await hello_world.getAddress());
}

main()
  .then(() => process.exit(0))
  .catch(error => {
    console.error(error);
    process.exit(1);
  });


