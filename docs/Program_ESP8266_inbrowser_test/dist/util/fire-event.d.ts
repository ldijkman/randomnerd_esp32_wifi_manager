export declare const fireEvent: <Event_1 extends keyof HTMLElementEventMap>(eventTarget: EventTarget, type: Event_1, detail?: HTMLElementEventMap[Event_1]["detail"] | undefined, options?: {
    bubbles?: boolean | undefined;
    cancelable?: boolean | undefined;
    composed?: boolean | undefined;
} | undefined) => void;
