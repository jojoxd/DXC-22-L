#!/usr/bin/env ts-node

import {LineParser} from "./src/LineParser";
import {ParsedLine} from "./src/ParsedLine";
import {TSVWriter} from "./src/TSVWriter";
import {SerialInput} from "./src/SerialInput";
import {Input} from "./src/Input";
import {resolve as resolvePath} from "path";
import {FileInput} from "./src/FileInput";
import {Writer} from "./src/Writer";
import {ConsoleWriter} from "./src/ConsoleWriter";

async function main()
{
    const dateObj = new Date();
    const date = `${dateObj.getFullYear()}-${dateObj.getMonth()+1}-${dateObj.getDate()}`;
    const time = `${dateObj.getHours()}.${dateObj.getMinutes()}.${dateObj.getSeconds()}`;

    const lineParser = new LineParser();

    // const writer: Writer = new TSVWriter(`data-${date}_${time}.tsv`);
    const writer: Writer = new ConsoleWriter();

    let input: Input;

    if(process.argv.includes("serial")) {
        const tty = await SerialInput.find('0483', '374b');
        if(!tty)
            throw new Error("Failed to find serial console");

        // console.log(`Connecting to ${tty}`);

        await new Promise<void>((resolve) => { setTimeout(() => { resolve() }, 2000) });

        input = new SerialInput(tty);
    } else if(process.argv.includes("file")) {
        input = new FileInput(resolvePath(process.cwd(), process.argv[process.argv.length - 1]));
    } else {
        throw new Error(`Usage: ${process.argv[1]} [ file <file-name> | serial ]`);
    }

    let tickData = {};
    input.getStream().on("data", (data) => {
        //// console.log(data);

        const line = lineParser.parseLine(data);
        writer.cacheOriginal(data);

        //// console.log(line);

        if(!line)
            return;

        if(!!line.tick) {
            writer.write(tickData as ParsedLine);

            tickData = {};
        }

        tickData = { ...tickData, ...line };
    });

    await input.sendSignal("p\n");

    let sigintCount = 0;
    process.on("SIGINT", async () => {
        // console.log("SIGINT");

        if(sigintCount++ >= 5) {
            process.exit();
        }

        await writer.close();
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
