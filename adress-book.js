var bob = {
    firstName: "Bob",
    lastName: "Jones",
    phoneNumber: "(650) 777-7777",
    email: "bob.jones@example.com"
};

var mary = {
    firstName: "Mary",
    lastName: "Johnson",
    phoneNumber: "(650) 888-8888",
    email: "mary.johnson@example.com"
};

var contacts = [bob, mary];

function printPerson(person) {
    console.log(person.firstName + " " + person.lastName);
}

function list() {
	var contactsLength = contacts.length;
	for (var i = 0; i < contactsLength; i++) {
		printPerson(contacts[i]);
	}}
	
	var search = function(lastName) {
    var contactsLength = contacts.length;
    for (var x = 0; x < contactsLength; x++) {
      if (contacts[x].lastName === lastName) {
        printPerson(contacts[x].lastName);
      }
    }
  };
	
function add(firstName, lastName,email, phoneNumber) {

    contacts[contacts.length] = {
    firstName: firstName,
    lastName: lastName,
    phoneNumber: phoneNumber,
    email: email
}

}

list();
 console.log("let's add a new person");
add("hideo","kojima","(650) 777-7777","blah");
list();
