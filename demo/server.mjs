import * as fs from "fs";
import * as http from "http";
import * as path from "path";
import * as url from "url";
const __dirname = path.dirname(url.fileURLToPath(import.meta.url));
const port = parseInt(process.argv[2] || 8080);
http.createServer((req, res) => {
    const pathname = path.join(__dirname, "..", path.normalize(new URL(req.url, 'http://-').pathname).replace(/^(\.\.[\/\\])+/, ""));
    fs.readFile(pathname, (err, data) => {
        if (err) {
            res.statusCode = 500;
            res.end(err.toString());
        } else {
            res.setHeader("Content-Type", {
                html: "text/html",
                css: "text/css",
                js: "text/javascript",
                mjs: "text/javascript",
                wasm: "application/wasm"
            }[path.parse(pathname).ext.substring(1)] || "text/plain");
            res.end(data);
        }
    });
}).listen(port);
console.log(`Listening on http://*:${port}`);