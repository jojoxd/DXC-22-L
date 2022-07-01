import {ParsedLine} from "./ParsedLine";

type ExtraData = { [key: string]: any };

export class LineParser
{
    protected static readonly regex: Readonly<RegExp> = /\[\s*(\d+\.\d+)]\s(\S+)\s+:\s(.+)/;

    public parseLine(line: string): ParsedLine | null
    {
        if(line.length === 0) {
            // console.log("Input line length = 0");
            return null;
        }

        const data = line.match(new RegExp(LineParser.regex));

        if(!data) {
            // console.log(`Regex failed for '${line}'`);
            return null;
        }

        return {
            timestamp: Number(data[1]),
            context: data[2],
            original: line,

            ...this.parseExtraData(data[3])
        };
    }

    protected parseExtraData(input: string): any
    {
        const mergeData: ExtraData = {
            'paper-thrower/raise': false,
            'paper-thrower/throw': false,
            'paper-thrower/lower': false,
        };

        const keypairs = input.split(", ");
        for(const keypair of keypairs) {
            if(keypair.indexOf("=") >= 0) {
                let [key, data] = keypair.split("=") as [string, any];

                switch(key) {
                    case "cny70/bias":
                        data = LineParser.convertBiasEnum(data);
                        break;

                    case 'tick':
                        data = parseInt(data);
                        break;

                    case 'cny70/left':
                    case 'cny70/center':
                    case 'cny70/right':
                        data = LineParser.convertIntoNumberWithUnit(data, "mV");
                        break;

                    case 'drv5053/pole':
                        data = LineParser.convertDRV5053Pole(data);
                        break;

                    case 'drv5053/voltage':
                        data = LineParser.convertIntoNumberWithUnit(data, "mV");
                        break;

                    case 'drv5053/tesla':
                        data = LineParser.convertIntoNumberWithUnit(data, "mT");
                        break;

                    case 'hc-sr04/distance':
                        data = LineParser.convertIntoNumberWithUnit(data, "cm");
                        break;

                    case 'drctl/leftSpeed':
                    case 'drctl/rightSpeed':
                        data = LineParser.convertIntoNumberWithUnit(data, "%");
                        break;

                    case 'pause':
                        data = true;
                        break;

                    default:
                        console.warn(`Unknown key: ${key}`);
                        break;
                }

                mergeData[key] = data;
            } else {
                mergeData[keypair] = true;
            }
        }

        return mergeData;
    }

    protected static convertBiasEnum(bias: string): string | null
    {
        return ({
            "0": "left",
            "1": "center",
            "2": "right"
        }[bias] ?? null);
    }

    protected static convertDRV5053Pole(pole: string): string | null
    {
        return ({
            "0": "North",
            "1": "South"
        }[pole] ?? null);
    }

    protected static convertIntoNumberWithUnit(data: string, unit: string): { value: number, unit: string }
    {
        return {
            value: parseInt(data),
            unit,
        };
    }
}