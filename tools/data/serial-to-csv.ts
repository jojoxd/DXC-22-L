#!/usr/bin/env ts-node

import {LineParser} from "./src/LineParser";
import {ParsedLine} from "./src/ParsedLine";
import {TSVWriter} from "./src/TSVWriter";
import {SerialInput} from "./src/SerialInput";
import {Input} from "./src/Input";
import {resolve as resolvePath} from "path";
import {FileInput} from "./src/FileInput";

async function main()
{
    const dateObj = new Date();
    const date = `${dateObj.getFullYear()}-${dateObj.getMonth()+1}-${dateObj.getDate()}`;
    const time = `${dateObj.getHours()}.${dateObj.getMinutes()}.${dateObj.getSeconds()}`;

    const lineParser = new LineParser();

    const tsv = new TSVWriter(`data-${date}_${time}.tsv`);

    let input: Input;

    if(process.argv.includes("serial")) {
        const tty = await SerialInput.find('0483', '374b');
        if(!tty)
            throw new Error("Failed to find serial console");

        input = new SerialInput(tty);
    } else if(process.argv.includes("file")) {
        input = new FileInput(resolvePath(process.cwd(), process.argv[process.argv.length - 1]));
    } else {
        throw new Error(`Usage: ${process.argv[1]} [ file <file-name> | serial ]`);
    }

    let tickData = {};
    input.getStream().on("data", (data) => {
        console.log(data);

        const line = lineParser.parseLine(data);

        console.log(line);

        if(!line)
            return;

        if(!!line.tick) {
            tsv.write(tickData as ParsedLine);

            tickData = {};
        }

        tickData = { ...tickData, ...line };
    });

    await input.sendSignal("p\n");

    process.on("SIGINT", async () => {
        await tsv.close();
        await input?.sendSignal("p\n"); // pause

        setTimeout(() => {
            input?.close();

            process.nextTick(() => {
                process.exit();
            })
        }, 50);
    });
}

main();
