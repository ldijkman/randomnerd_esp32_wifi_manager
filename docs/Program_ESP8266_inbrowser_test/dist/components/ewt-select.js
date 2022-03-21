import { SelectBase } from "@material/mwc-select/mwc-select-base";
import { styles } from "@material/mwc-select/mwc-select.css";
export class EwtSelect extends SelectBase {
}
EwtSelect.styles = [styles];
customElements.define("ewt-select", EwtSelect);
