'use strict';

var fs = require('fs');
var toml = require('toml');

const assert = require('assert');
const request = require('supertest');

var app;

describe('/api/hello', function() {

    before(function(){
        const contents = fs.readFileSync('config.toml').toString();
        const config = toml.parse(contents);
        app = "http://localhost:" + config.Server.port;
    })

    it('GET /api/hello should return 200 OK with content-type json', function(done) {
        request(app)
        .get('/hello')
        .expect(200)
        .expect(function(res) {
            assert.equal(res.text, 'world');
        })
        .end(done);
    });
});

