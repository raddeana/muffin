var dns = require('dns');

dns.lookup('www.github.com', function onLookup (err, address, family) {
  console.info('ip 地址:', address);

  dns.reverse(address, function (err, hostnames) {

    if (err) {
      console.info(err.stack);
    }

    console.info('反向解析 ' + address + ': ' + JSON.stringify(hostnames));
  });  
});
