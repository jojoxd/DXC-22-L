import {Input} from "./Input";
import {Readable} from "stream";
import {createReadStream} from "fs";
import {ReadlineParser} from "@serialport/parser-readline";

export class FileInput implements Input
{
    protected fd: Readable

    constructor(path: string)
    {
        this.fd = createReadStream(path, "utf-8");
    }

    getStream(): Readable
    {
        const readlineParser = new ReadlineParser({ delimiter: '\r\n', encoding: "ascii", includeDelimiter: false });

        return this.fd.pipe(readlineParser);
    }

    async sendSignal(signal: string): Promise<void>
    {
        // NOOP
    }

    async close(): Promise<void>
    {
        this.fd.destroy();
    }
}
