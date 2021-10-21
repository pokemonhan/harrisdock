db.createUser(
    {
        user: "user",
        pwd: "userpassword",
        roles: [ "readWrite", "dbAdmin" ]
    }
)
