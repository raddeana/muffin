#### 嵌入式关系
"_id":ObjectId("52ffc33cd85242f436000001"),
"contact": "987654321",
"dob": "01-01-1991",
"name": "Tom Benzamin",
"address": [{
  "building": "22 A, Indiana Apt",
  "pincode": 123456,
  "city": "Los Angeles",
  "state": "California"
}, {
  "building": "170 A, Acropolis Apt",
  "pincode": 456789,
  "city": "Chicago",
  "state": "Illinois"
}]

#### query
db.users.findOne({ "name": "Tom Benzamin" }, { "address" : 1 })

#### 引用式关系
{
  "_id":ObjectId("52ffc33cd85242f436000001"),
  "contact": "987654321",
  "dob": "01-01-1991",
  "name": "Tom Benzamin",
  "address_ids": [
    ObjectId("52ffc4a5d85242602e000000"),
    ObjectId("52ffc4a5d85242602e000001")
  ]
}

#### query
db.users.findOne({"name": "Tom Benzamin"}, {"address_ids": 1})
db.address.find({"_id": {"$in": result["address_ids"]}})
