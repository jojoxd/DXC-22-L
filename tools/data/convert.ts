#!/usr/bin/env ts-node

import {readFileSync, writeFileSync} from "fs";
import { resolve as resolvePath } from "path";

const data = readFileSync(resolvePath(process.cwd(), "data.txt")).toString("utf-8");
const lines = data.split(/\r?\n/);

function parseLine(input: string): ParsedLine | null
{
    if(input.length === 0)
        return null;

    const data = input.match(/\[\s+(\d+\.\d+)]\s(\S+)\s+:\s(.+)/);

    if(!data)
        throw new Error(`Regex failed for '${input}'`);

    const extraData = data[3].split(", ");

    const _mergeData: {[key: string]: any} = {};

    for(const extra of extraData) {
        if(extra.indexOf("=") >= 0) {
            let [key, data] = extra.split("=") as [string, any];

            // convert data
            switch(key) {
                case "cny70/bias":
                    switch(data) {
                        case "0":
                            data = "left";
                            break;

                        case "1":
                            data = "center";
                            break;

                        case "2":
                            data = "right";
                            break;

                        default:
                            throw new Error("Failed to parse cny70/bias: '${data}' is not a valid enum");
                    }

                    break;

                case 'tick':
                    data = parseInt(data);
                    break;

                case 'cny70/left':
                case 'cny70/center':
                case 'cny70/right':
                    data = { value: parseInt(data), unit: 'mV' };
                    break;

                case 'hc-sr04/distance':
                    data = { value: parseInt(data), unit: 'cm' };
                    break;

                case 'drctl/leftSpeed':
                case 'drctl/rightSpeed':
                    data = { value: parseInt(data), unit: '%' };
                    break;
            }

            _mergeData[key] = data;
        } else {
            _mergeData[extra] = true;
        }
    }

    return {
        timestamp: Number(data[1]),
        context: data[2],

        ..._mergeData,
    };
}

const tickMap: Map<number, Array<ParsedLine>> = new Map<number, Array<ParsedLine>>();

let tick = 0;
for(let line of lines) {

    const pl = parseLine(line);

    if(pl === null)
        continue;

    if(!!pl.tick) {
        tick = Number(pl.tick);
    }

    // console.log(pl);

    const map = tickMap.get(tick) ?? [];

    map.push(pl);

    tickMap.set(tick, map);
}

const csv = [];

// Headers
csv.push([
    'timestamp',
    'tick',

    'cny70/bias',
    'cny70/left',
    'cny70/center',
    'cny70/right',

    'hc-sr04/distance',

    'drctl/leftSpeed',
    'drctl/rightSpeed'
]);

for(let key of Array.from(tickMap.keys()).sort((a,b) => a - b)) {
    const tickData = tickMap.get(key)!;

    const tick = tickData.reduce<any>((acc, tick) => {
        return { ...acc, ...tick };
    }, {});

    csv.push([
        tick.timestamp,
        tick.tick,

        tick['cny70/bias'],
        tick['cny70/left']?.value ?? '',
        tick['cny70/center']?.value ?? '',
        tick['cny70/right']?.value ?? '',

        tick['hc-sr04/distance']?.value ?? '',

        tick['drctl/leftSpeed']?.value ?? '',
        tick['drctl/rightSpeed']?.value ?? '',
    ]);
}

writeFileSync(
    resolvePath(process.cwd(), "test.csv"),
    csv
        .map(line => line.join("\t"))
        .join("\n")
);

interface ParsedLine
{
    timestamp: number;
    context: string;

    [key: string]: any;
}