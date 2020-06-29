'use strict';

const express = require('express');
const { Server } = require('ws');

const PORT = process.env.PORT || 5000;
const INDEX = '/index2.html';

console.log(PORT);

const server = express()
    .use(express.static('public'))
    .use((req, res) => res.sendFile(INDEX, { root: __dirname }))
    .listen(PORT, () => console.log(`Hello!: Listening on ${PORT}`));

const wss = new Server({ server });

wss.on('connection', (ws) => {
    
    console.log('Hello! Client connected');

    ws.on('message', function incoming(data) {
        console.log(data);
        wss.clients.forEach(function each(client) {
            client.send(data);
        });
    });


    ws.on('close', () => console.log(' Hello! Client disconnected'));
});