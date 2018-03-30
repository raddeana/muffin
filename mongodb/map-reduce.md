db.collection.mapReduce(
  function() {emit(key,value);},                  // map 函数
  function(key,values) {return reduceFunction},   // reduce 函数
  {
    out: collection,
    query: document,
    sort: document,
    limit: number
  }
)
