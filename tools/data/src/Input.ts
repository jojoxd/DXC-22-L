import {Readable} from "stream";

export interface Input
{
    getStream(): Readable;

    close(): Promise<void>;

    sendSignal(signal: string): Promise<void>;
}