var friends = {};
friends.magda = {
  firstName: "Magda",
  lastName: "Kowalska",
  number: "(206) 555-5555",
  address: ['Kolejowa 76','Kazimierza Wielka','PL','28-500']
};
friends.adrian = {
  firstName: "Adrian",
  lastName: "Kowalski",
  number: "513-987-725",
  address: ['Kolejowa 76','Kazimierza Wielka','PL','28-500']
};

var list = function(obj) {
  for(var prop in obj) {
    console.log(prop);
  }
};

var search = function(name) {
  for(var prop in friends) {
    if(friends[prop].firstName === name) {
      console.log(friends[prop]);
      return friends[prop];
    }
  }
};

list(friends);
search("Adrian");
