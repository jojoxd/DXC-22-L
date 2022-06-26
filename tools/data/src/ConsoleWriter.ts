import {Writer} from "./Writer";
import {ParsedLine} from "./ParsedLine";
import * as cliui from "cliui";

// @ts-ignore
import {ScreenBuffer, terminal, TextBuffer, TextBox} from "terminal-kit";

export class ConsoleWriter implements Writer
{
    protected doc: Document;

    protected log: TextBox;

    constructor()
    {
        // @ts-ignore
        this.doc = terminal.createDocument();

        this.log = new TextBox({
            parent: this.doc,

            x: 0, y: 0,

            width: terminal.width,
            height: terminal.height - 15,
            scrollable: true,
        });

        const buffers = [
            'cny70/left',
            'cny70/center',
            'cny70/right',
            'cny70/bias',
            'drctl/leftSpeed',
            'drctl/rightSpeed',
            'tick',
            'timestamp',
            'hc-sr04/distance',
            'drv5053/pole',
            'drv5053/voltage',
            'drv5053/tesla',
            'paper-thrower/raise',
            'paper-thrower/throw',
            'paper-thrower/lower',
        ];

        for(const name of buffers) {
            this.buffers.set(name, new TextBox({
                parent: this.doc,
            }));

            if(name.startsWith('paper-thrower')) {
                this.buffers.get(name).textBuffer.setText(`${name}: \nFalse`);
            }
        }

        terminal.on('resize', () => {
            this.resize();
        });

        this.resize();
    }

    protected resize()
    {
        const width = Math.floor(terminal.width / 3) - 1;

        const columns = 4;

        // ROW 1
        this.log.setSizeAndPosition({
            x: 1, y: 1,
            width: terminal.width,
            height: terminal.height - 16
        });


        // ROW 2
        this.buffers.get('cny70/left').setSizeAndPosition({
            x: 0, y: terminal.height - 14,
            width,
            height: 2
        });

        this.buffers.get('cny70/right').setSizeAndPosition({
            x: Math.floor(terminal.width / columns), y: terminal.height - 14,
            width,
            height: 2
        });

        this.buffers.get('cny70/center').setSizeAndPosition({
            x: Math.floor(terminal.width / columns) * 2, y: terminal.height - 14,
            width,
            height: 2
        });


        // ROW 3
        this.buffers.get('cny70/bias').setSizeAndPosition({
            x: 0, y: terminal.height - 11,
            width,
            height: 2
        });

        this.buffers.get('hc-sr04/distance').setSizeAndPosition({
            x: Math.floor(terminal.width / columns), y: terminal.height - 11,
            width,
            height: 2
        });


        // ROW 4
        this.buffers.get('tick').setSizeAndPosition({
            x: 0, y: terminal.height - 8,
            width,
            height: 2
        });

        this.buffers.get('timestamp').setSizeAndPosition({
            x: Math.floor(terminal.width / columns), y: terminal.height - 8,
            width,
            height: 2
        });


        // ROW 5
        this.buffers.get('drctl/leftSpeed').setSizeAndPosition({
            x: 0, y: terminal.height - 5,
            width,
            height: 2
        });

        this.buffers.get('drctl/rightSpeed').setSizeAndPosition({
            x: Math.floor(terminal.width / columns), y: terminal.height - 5,
            width,
            height: 2
        });


        // ROW 6
        this.buffers.get('drv5053/pole').setSizeAndPosition({
            x: 0, y: terminal.height -2,
            width,
            height: 2
        });

        this.buffers.get('drv5053/voltage').setSizeAndPosition({
            x: Math.floor(terminal.width / columns), y: terminal.height - 2,
            width,
            height: 2
        });

        this.buffers.get('drv5053/tesla').setSizeAndPosition({
            x: Math.floor(terminal.width / columns) * 2, y: terminal.height - 2,
            width,
            height: 2
        });


        // COL 4
        this.buffers.get('paper-thrower/raise').setSizeAndPosition({
            x: Math.floor(terminal.width / columns) * 3, y: terminal.height - 14,
            width,
            height: 2
        });

        this.buffers.get('paper-thrower/throw').setSizeAndPosition({
            x: Math.floor(terminal.width / columns) * 3, y: terminal.height - 11,
            width,
            height: 2
        });

        this.buffers.get('paper-thrower/lower').setSizeAndPosition({
            x: Math.floor(terminal.width / columns) * 3, y: terminal.height - 8,
            width,
            height: 2
        });
    }

    protected lines: Array<string> = [];

    protected uiSize: number = 16;

    protected isSetup = false;

    protected buffers: Map<string, TextBox> = new Map<string, TextBox>();

    write(line: ParsedLine)
    {
        for(const [key, value] of Object.entries(line)) {
            const box = this.buffers.get(key) ?? undefined;

            // @TODO: Decode contents of value
            box?.textBuffer.setText(`${key}:\n${this.convertToString(key, value)}`);

            switch(key) {
                case 'hc-sr04/distance':
                    box?.textBuffer.setAttrRegion({
                        color: value.value > 20 ? 'green' : 'red'
                    });
                    break;

                case 'paper-thrower/raise':
                case 'paper-thrower/throw':
                case 'paper-thrower/lower':
                    box?.textBuffer.setAttrRegion({
                        color: !!value ? 'green' : undefined,
                        defaultColor: !value,
                    });
                    break;

                case 'drv5053/tesla':
                    box?.textBuffer.setAttrRegion({
                        color: value.value > 5 ? 'green' : 'red',
                    });
            }
        }

        this.log.redraw();
    }

    cacheOriginal(line: string)
    {
        this.log.appendLog(line, true);
    }

    close()
    {
    }

    protected static readonly unitTypes: ReadonlyArray<string> = [
        'cny70/left',
        'cny70/center',
        'cny70/right',
        'drv5053/voltage',
        'drv5053/tesla',
        'hc-sr04/distance',
        'drctl/leftSpeed',
        'drctl/rightSpeed',
    ];

    convertToString(key: string, value: any)
    {
        if(ConsoleWriter.unitTypes.indexOf(key) >= 0)
            return `${value.value} ${value.unit}`;

        if(value instanceof Boolean)
            return value ? "True" : "False";

        if(value instanceof Number)
            return value.toString();

        return value;
    }
}