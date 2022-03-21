import { TextFieldBase } from "@material/mwc-textfield/mwc-textfield-base";
import { styles } from "@material/mwc-textfield/mwc-textfield.css";
export class EwtTextfield extends TextFieldBase {
}
EwtTextfield.styles = [styles];
customElements.define("ewt-textfield", EwtTextfield);
