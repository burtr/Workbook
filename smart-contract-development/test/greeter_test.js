

const GreeterContract = artifacts.require("Greeter") ;

contract ( "Greeter", ()=>{
	it("has been deployed succesfully", async ()=> {
			const greeter = await GreeterContract.deployed() ;
			assert( greeter, "contract was not deployed") ;
	}) ;

	describe ( "greet()", ()=> {
		it ( "returns 'Hello World!'", async ()=> {
			const greeter = await GreeterContract.deployed() ;
			const expected = "Hello World!" ;
			const actual = await greeter.greet() ;
			assert.equal( actual, expected, "greeted with 'Hello World!'") ;
		}) ;
		
	}) ;

}) ;
