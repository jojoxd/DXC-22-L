import {createWriteStream, WriteStream} from "fs";
import {ParsedLine} from "./ParsedLine";


export class TSVWriter
{
    protected fd: WriteStream;

    constructor(fileName: string)
    {
        this.fd = createWriteStream(fileName, { flags: 'as' });
    }

    protected writeHeader()
    {
        this.fd.write([
            'timestamp',
            'tick',

            'cny70/bias',
            'cny70/left',
            'cny70/center',
            'cny70/right',

            'hc-sr04/distance',

            'drctl/leftSpeed',
            'drctl/rightSpeed',
        ].join('\t') + '\n');
    }

    public write(tick: ParsedLine)
    {
        this.fd.write([
            tick.timestamp ?? '',
            tick.tick ?? '',

            tick['cny70/bias'] ?? '',
            tick['cny70/left']?.value ?? '',
            tick['cny70/center']?.value ?? '',
            tick['cny70/right']?.value ?? '',

            tick['hc-sr04/distance']?.value ?? '',

            tick['drctl/leftSpeed']?.value ?? '',
            tick['drctl/rightSpeed']?.value ?? '',
        ].join("\t") + "\n");
    }

    public async close(): Promise<void>
    {
        return new Promise<void>((resolve, reject) => {
            this.fd.close((err) => {
                if(err) reject(err);
                else resolve();
            });
        });
    }
}
