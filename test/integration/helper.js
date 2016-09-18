'use strict';

const path = require('path');
const fs = require('fs');
const spawn = require('child_process').spawn;

const toml = require('toml');
const couchbase = require("couchbase");
const async = require('async');

var crowbase;

before(function(done) {
    
    // @
    console.log('Start crowbase');
    var parentDir = path.resolve(process.cwd(), '../build');
    console.log(parentDir);

    crowbase = spawn('./crowbase', [], {
        cwd: parentDir,
        detached: true,
        stdio: 'ignore'
    });

    crowbase.on('error', (err) => {
        console.log('Failed to start child process.', err);
    });

    // @
    console.log('Delete documents in buckets');
    const contents = fs.readFileSync('config.toml').toString();
    const config = toml.parse(contents);
    
    var bucket = (new couchbase.Cluster(config.Database.cluster)).openBucket(config.Database.bucket,config.Database.password);

    var ViewQuery = couchbase.ViewQuery;
    var query = ViewQuery.from('dev_docs', 'by_id');
    query.range("user:", "user:" + "\u02ad", false);

    bucket.query(query, function(error, results) {
        if(error) {
            return console.log(error);
        }
        console.log("Found " + results.length + " documents to delete");

        async.each(results, function(document, cb) {
            bucket.remove(document.id, function(err, result) {
                if (err) return cb(err);
                console.log("Deleting " + document.key);
                cb();
            })
        }, function(err) {
            done();
        });
    });    
});

after(function(done) {
    console.log('Kill crowbase');
    crowbase.kill();
    done();
});


