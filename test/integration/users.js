'use strict';

var fs = require('fs');
var toml = require('toml');

const assert = require('assert');
const request = require('supertest');

var app;

describe('/api/users', function() {

    before(function(){
        const contents = fs.readFileSync('config.toml').toString();
        const config = toml.parse(contents);
        app = "http://localhost:" + config.Server.port;
    })

    it('POST /api/users should return 201 Created with response contain original data', function(done) {
        request(app)
        .post('/users')
        .set('Content-Type', 'application/json')
        .set('Accept', 'application/json')
        .send({name: 'jim', email: 'jim@company.com', position_id: 1, position: 'CEO'})
        .expect(201)
        .expect('Content-Type', /json/)
        .expect(function(res) {
            assert(res.body.data, 'Response body has data');
            assert(res.body.data._entity, 'Data has _entity field');
            assert(res.body.data.email, 'Data has email field');
            assert.equal(res.body.data.email, 'jim@company.com', 'Email field is equal to sent value');
        })
        .end(done);
    });

    it('GET /api/users should return 200 OK with list of users', function(done) {
        request(app)
        .get('/users')
        .set('Accept', 'application/json')
        .expect(200)
        .expect('Content-Type', /json/)
        .expect(function(res) {
            assert(res.body.data, 'Response body has data');
            assert.equal(res.body.data.constructor, Array, 'Data is an array');
            assert.equal(res.body.data.length, 1, 'Data should contain 1 item');
        })
        .end(done);
    });

});

