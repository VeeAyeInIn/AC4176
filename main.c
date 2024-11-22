
#include <stdio.h>
#include "src/bignumber.h"
#include <time.h>



/**
 * TODO
 *
 * Command-Line Options:
 *
 *      h       TODO
 *      v       TODO
 *
 * @param argc TODO
 * @param argv TODO
 *
 * @return TODO
 */
int main(int argc, char* argv[]) {

    uintx_t p;
    uintx_t q;
    uintx_t n;
    uintx_t e;
    uintx_t d;
    uintx_t m; // Plaintext
    uintx_t c; // Ciphertext

    uintx_init(&p);
    uintx_init(&q);
    uintx_init(&n);
    uintx_init(&e);
    uintx_init(&d);
    uintx_init(&m);
    uintx_init(&c);

    // Random Message.
    uintx_parse_hex(&m, "0xC0DECAFE");

    // 9044459790914257129112932576732594903134617383811122998454955588441570819962597674868984141343258173
    uintx_parse_hex(&p, "0x108A52C75AC2A6A05E1480AF2CF9C48F3844B2DA22AEBF4EAC058051E3FE2C636AD9326D8BC58E9E763D");

    // 1667148657579611658143270289333188989716847291499711315277428757436384925488802534782314577338121087
    uintx_parse_hex(&q, "0x30C814AA0F7609D50BCC9500CF381A025D7B2D52FF42B4F3930A9D88A632C565D506E9C515E60B13B7F");

    // 65537 (Common 'e')
    uintx_parse_hex(&e, "0x10001");

    // Compute n = pq.
    uintx_mul(&n, &p, &q);

    // Compute d = e^(-1) (mod n)
    // Couldn't get a working mod inverse working yet, so had to use python.
    uintx_parse_hex(&d, "0x540217308231189472876529069950867827585486463975650131726347209390889030125300531184821767335666687273196507631069573808454237498395519409531852691709132079151755289533462359243694808558324845894277");

    // Compute c = m^d (mod n)
    uintx_sqmul(&c, &m, &d, &n);

    // Compute m = c^e = (m^d)^e = m (mod n)
    uintx_t decrypted;
    uintx_init(&decrypted);
    uintx_sqmul(&decrypted, &c, &e, &n);

    if (uintx_equal(&decrypted, &m)) {
        fprintf(stdout, "Success!\n");
    } else {
        fprintf(stdout, "Failure\n");
    }

    uintx_free(&p);
    uintx_free(&q);
    uintx_free(&n);
    uintx_free(&e);
    uintx_free(&d);
    uintx_free(&m);
    uintx_free(&c);
    uintx_free(&decrypted);

    return 0;

}
