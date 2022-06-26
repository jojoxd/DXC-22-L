import {SerialPort} from "serialport";
import {Input} from "./Input";
import {ReadlineParser} from "@serialport/parser-readline";
import {Readable} from "stream";

export class SerialInput implements Input
{
    protected port: SerialPort;

    constructor(path: string)
    {
        this.port = new SerialPort({ path: path, baudRate: 115200 }, (err) => {
            if(err) {
                console.warn("Connection Error:", err);
                return;
            }

            // console.log(`Connected to ${path}`);
        });

        this.port.on("close", () => {
            // console.log(`Connection to ${path} closed`);
        });

        this.port.on("error", (err) => {
            console.warn("Connection Error:", err);
        })
    }

    getStream(): Readable
    {
        const readlineParser = new ReadlineParser({ delimiter: '\r\n', encoding: "ascii", includeDelimiter: false });

        return this.port.pipe(readlineParser);
    }

    async sendSignal(signal: string)
    {
        return new Promise<void>((resolve, reject) => {
            this.port.write(signal, (err) => {
                if(err) reject(err)
                else resolve();
            });
        });
    }

    async close()
    {
        return new Promise<void>((resolve, reject) => {
            this.port.close((err) => {
                if(err) reject(err)
                else resolve();
            });
        });
    }

    static async find(vid: string, pid: string): Promise<string | null>
    {
        const ports = await SerialPort.list();

        const port = ports.find((port) => {
            return port.vendorId === vid && port.productId === pid;
        });

        return port?.path ?? null;
    }
}
