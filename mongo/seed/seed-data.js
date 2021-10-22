db.createUser(
    {
        user: "user",
        pwd: "userpassword",
        roles: [ { role: "userAdminAnyDatabase", db: "dbAdmin" }, "readWriteAnyDatabase" ]
    }
)
