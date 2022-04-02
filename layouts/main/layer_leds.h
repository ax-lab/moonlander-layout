#pragma once

/*
	LED layout:

	+------------------------+   +------------------------+
	|  A0 B0 C0 D0 E0 F0 G0  |   |  H0 I0 J0 K0 L0 M0 N0  |
	|  A1 B1 C1 D1 E1 F1 G1  |   |  H1 I1 J1 K1 L1 M1 N1  |
	|  A2 B2 C2 D2 E2 F2 G2  |   |  H2 I2 J2 K2 L2 M2 N2  |
	|  A3 B3 C3 D3 E3 F3     |   |     I3 J3 K3 L3 M3 N3  |
	|  A4 B4 C4 D4 E4    X3  |   |  Y3    J4 K4 L4 M4 N4  |
	|              X0 X1 X2  |   |  Y2 Y1 Y0              |
	+------------------------+   +------------------------+
*/

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {

	//  A0   A1   A2   A3   A4  <-- Leftmost
	//  B0   B1   B2   B3   B4
	//  C0   C1   C2   C3   C4
	//  D0   D1   D2   D3   D4
	//  E0   E1   E2   E3   E4
	//  F0   F1   F2   F3
	//  G0   G1   G2
	//  X0   X1   X2   X3       <-- Left thumb
	//
	//  N0   N1   N2   N3   N4  <-- Rightmost
	//  M0   M1   M2   M3   M4
	//  L0   L1   L2   L3   L4
	//  K0   K1   K2   K3   K4
	//  J0   J1   J2   J3   J4
	//  I0   I1   I2   I3
	//  H0   H1   H2
	//  Y0   Y1   Y2   Y3       <-- Right thumb

	[LAYER_BASE] = {
		ORG, RED, RED, RED, RED, // A
		RED, PNK, PNK, PNK, RED, // B
		RED, PNK, PNK, PNK, RED, // C
		RED, PNK, PNK, PNK, RED, // D
		RED, PNK, PNK, PNK, RED, // E
		RED, PNK, PNK, PNK,      // F
		RED, RED, RED,           // G
		RED, RED, RED, RED,      // X

		RED, RED, RED, RED, RED, // N
		RED, PNK, PNK, PNK, RED, // M
		RED, PNK, PNK, PNK, RED, // L
		RED, PNK, PNK, PNK, RED, // K
		RED, PNK, PNK, PNK, RED, // J
		RED, PNK, PNK, PNK,      // I
		RED, RED, RED,           // H
		RED, RED, RED, RED       // Y
	},

	[LAYER_GAME] = {
		RED, PNK, GRN, GRN, PNK, // A
		PNK, PNK, BLU, PNK, GRN, // B
		PNK, BLU, BLU, PNK, PNK, // C
		PNK, PNK, BLU, PNK, ORY, // D
		PNK, PNK, PNK, PNK, PNK, // E
		PNK, PNK, PNK, PNK,      // F
		RED, PNK, PNK,           // G
		ORY, GRN, PNK, PNK,      // X

		PNK, PNK, PNK, PNK, PNK, // N
		PNK, PNK, PNK, PNK, PNK, // M
		PNK, PNK, BLU, PNK, PNK, // L
		PNK, BLU, BLU, PNK, PNK, // K
		PNK, PNK, BLU, PNK, PNK, // J
		PNK, PNK, PNK, PNK,      // I
		PNK, PNK, PNK,           // H
		PNK, PNK, PNK, ORY       // Y
	},

	[LAYER_G_TYPE] = {
		BLU, BLU, BLU, GRN, GRN, // A
		BLU, BLU, BLU, GRN, GRN, // B
		PUR, PUR, PUR, NAV, NAV, // C
		PUR, PUR, PUR, NAV, NAV, // D
		PNK, PNK, PNK, ORG, ORG, // E
		PNK, PNK, PNK, ORG,      // F
		RED, RED, RED,           // G
		BLU, BLU, BLU, BLU,      // X

		NAV, NAV, NAV, BLU, BLU, // N
		NAV, NAV, NAV, BLU, BLU, // M
		GRN, GRN, GRN, PUR, PUR, // L
		GRN, GRN, GRN, PUR, PUR, // K
		ORG, ORG, ORG, PNK, PNK, // J
		ORG, ORG, ORG, PNK,      // I
		RED, RED, RED,           // H
		BLU, BLU, BLU, WHI       // Y
	},

	[LAYER_MODS] = {
		PNK, PNK, PNK, PNK, PNK, // A
		PNK, PNK, GRN, PNK, PNK, // B
		PNK, PNK, GRN, PNK, PNK, // C
		PNK, PNK, GRN, PNK, PNK, // D
		PNK, PNK, GRN, PNK, PNK, // E
		PNK, PNK, PNK, PNK,      // F
		PNK, YLW, BLU,           // G
		PNK, PNK, PNK, PNK,      // X

		PNK, PNK, PNK, PNK, PNK, // N
		PNK, PNK, GRN, PNK, PNK, // M
		PNK, PNK, GRN, ORY, PNK, // L
		PNK, PNK, GRN, ORY, PNK, // K
		PNK, PNK, GRN, ORY, PNK, // J
		PNK, PNK, PNK, PNK,      // I
		PNK, YLW, BLU,           // H
		PNK, PNK, PNK, PNK       // Y
	},

	[LAYER_SYM] = {
		PNK, PNK, PNK, PNK, PNK, // A
		ORY, PNK, PNK, PNK, PNK, // B
		ORY, PNK, PNK, PNK, PNK, // C
		ORY, PNK, PNK, PNK, RED, // D
		ORY, PNK, PNK, PNK, RED, // E
		ORY, PNK, PNK, PNK,      // F
		PNK, PNK, RED,           // G
		PNK, GRN, GRN, RED,      // X

		ORY, ORY, PNK, PNK, PNK, // N
		ORY, PNK, PNK, PNK, PNK, // M
		ORY, PNK, PNK, PNK, PNK, // L
		ORY, PNK, PNK, PNK, PNK, // K
		ORY, PNK, PNK, PNK, PNK, // J
		ORY, PNK, PNK, PNK,      // I
		PNK, PNK, RED,           // H
		PNK, PNK, PNK, PNK       // Y
	},

	[LAYER_NUM] = {
		RED, BLU, RED, RED, RED, // A
		RED, PNK, YLW, PNK, RED, // B
		RED, PNK, YLW, PNK, RED, // C
		RED, PNK, YLW, PNK, GRN, // D
		RED, PNK, YLW, PNK, RED, // E
		RED, PNK, YLW, PNK,      // F
		RED, BLU, PNK,           // G
		RED, RED, RED, RED,      // X

		RED, RED, RED, RED, RED, // N
		RED, PNK, YLW, PNK, RED, // M
		RED, PNK, YLW, PNK, RED, // L
		RED, PNK, YLW, PNK, RED, // K
		RED, PNK, YLW, YLW, RED, // J
		RED, PNK, PNK, PNK,      // I
		RED, RED, RED,           // H
		RED, RED, RED, RED       // Y
	},

	[LAYER_NAV] = {
		BLU, BLU, PNK, BLU, BLU, // A
		PNK, BLU, ORY, PNK, PNK, // B
		PNK, ORY, BLU, ORY, PNK, // C
		PNK, BLU, BLU, ORY, PNK, // D
		PNK, ORY, BLU, ORY, PNK, // E
		PNK, PNK, ORY, PNK,      // F
		PNK, PNK, PNK,           // G
		PNK, PNK, PNK, PNK,      // X

		PNK, PNK, PNK, PNK, PNK, // N
		PNK, PNK, GRN, PNK, PNK, // M
		PNK, BLU, GRN, PNK, PNK, // L
		PNK, BLU, GRN, BLU, PNK, // K
		PNK, BLU, GRN, BLU, GRN, // J
		PNK, PNK, PNK, PNK,      // I
		PNK, PNK, PNK,           // H
		PNK, PNK, PNK, PNK       // Y
	},

	[LAYER_FN] = {
		BLU, PNK, PNK, PNK, BLU, // A
		ORY, ORY, GRN, PNK, PNK, // B
		ORY, ORY, GRN, PNK, PNK, // C
		ORY, ORY, GRN, PNK, PNK, // D
		ORY, ORY, GRN, PNK, PNK, // E
		ORY, ORY, PNK, PNK,      // F
		YLW, YLW, ORY,           // G
		PNK, PNK, PNK, PNK,      // X

		PNK, PNK, PNK, PNK, PNK, // N
		PNK, YLW, YLW, YLW, PNK, // M
		PNK, ORY, ORY, ORY, PNK, // L
		PNK, ORY, ORY, ORY, PNK, // K
		PNK, ORY, ORY, ORY, PNK, // J
		PNK, YLW, YLW, YLW,      // I
		PNK, PNK, BLU,           // H
		PNK, PNK, PNK, PNK       // Y
	},

	[LAYER_ACC] = {
		PNK, PNK, PNK, PNK, PNK, // A
		ORY, ORY, ORY, ORY, PNK, // B
		PNK, ORY, ORY, ORY, PNK, // C
		PNK, PNK, ORY, ORY, PNK, // D
		ORY, ORY, ORY, ORY, PNK, // E
		ORY, ORY, ORY, ORY,      // F
		PNK, PNK, PNK,           // G
		PNK, PNK, PNK, PNK,      // X

		PNK, PNK, PNK, PNK, PNK, // N
		PNK, PNK, PNK, PNK, PNK, // M
		ORY, ORY, ORY, ORY, PNK, // L
		PNK, PNK, ORY, PNK, PNK, // K
		ORY, ORY, ORY, ORY, PNK, // J
		PNK, PNK, ORY, PNK,      // I
		PNK, PNK, PNK,           // H
		PNK, PNK, PNK, PNK       // Y
	},

	[LAYER_G_MOD_A] = {
		WHI, PNK, YLW, PNK, PNK, // A
		ORY, YLW, YLW, YLW, PNK, // B
		ORY, YLW, YLW, YLW, PNK, // C
		ORY, YLW, YLW, YLW, PNK, // D
		ORY, PNK, BLU, BLU, PNK, // E
		ORY, PNK, PNK, PNK,      // F
		PNK, PNK, PNK,           // G
		PNK, PNK, PNK, PNK,      // X

		ORY, ORY, PNK, PNK, PNK, // N
		ORY, PNK, PNK, PNK, PNK, // M
		ORY, PNK, PNK, PNK, PNK, // L
		ORY, PNK, PNK, PNK, PNK, // K
		ORY, PNK, PNK, PNK, PNK, // J
		ORY, PNK, PNK, PNK,      // I
		PNK, PNK, PNK,           // H
		PNK, PNK, PNK, PNK       // Y
	},

	[LAYER_G_MOD_B] = {
		PNK, YLW, YLW, YLW, PNK, // A
		PNK, ORY, ORY, ORY, PNK, // B
		PNK, ORY, ORY, ORY, PNK, // C
		PNK, ORY, ORY, ORY, PNK, // D
		PNK, PNK, BLU, PNK, PNK, // E
		PNK, BLU, BLU, BLU,      // F
		PNK, PNK, PNK,           // G
		PNK, PNK, PNK, PNK,      // X

		PNK, PNK, PNK, PNK, PNK, // N
		PNK, PNK, PNK, PNK, PNK, // M
		PNK, PNK, PNK, PNK, PNK, // L
		PNK, PNK, PNK, PNK, PNK, // K
		PNK, PNK, PNK, PNK, PNK, // J
		PNK, PNK, PNK, PNK,      // I
		PNK, PNK, PNK,           // H
		PNK, PNK, PNK, PNK       // Y
	},

	[LAYER_UTIL] = {
		ORY, PNK, PNK, PNK, PNK, // A
		PNK, PNK, PNK, PNK, PNK, // B
		PNK, RED, PNK, PNK, RED, // C
		PNK, BLU, PNK, PNK, ORY, // D
		RED, BLU, PNK, PNK, ORY, // E
		PNK, PNK, PNK, PNK,      // F
		PNK, PNK, YLW,           // G
		GRN, ORY, ORY, BLU,      // X

		RED, PNK, PNK, BLU, WHI, // N
		GRN, YLW, YLW, YLW, PNK, // M
		PNK, PNK, PNK, YLW, PNK, // L
		PNK, PNK, PNK, PNK, BLU, // K
		PNK, RED, RED, PNK, BLU, // J
		PNK, ORY, ORY, PNK,      // I
		WHI, GRN, GRN,           // H
		PNK, PNK, PNK, BLU       // Y
	},

	[LAYER_PAD] = {
		RED, PNK, RED, PNK, PNK, // A
		PNK, ORY, ORY, ORY, PNK, // B
		PNK, PNK, BLU, BLU, PNK, // C
		PNK, BLU, BLU, BLU, BLU, // D
		RED, PNK, BLU, BLU, PNK, // E
		PNK, PNK, PNK, ORY,      // F
		PNK, WHI, RED,           // G
		ORY, ORY, PNK, ORY,      // X

		YLW, ORY, RED, BLU, PNK, // N
		YLW, PNK, BLU, BLU, BLU, // M
		PNK, YLW, YLW, YLW, PNK, // L
		PNK, YLW, YLW, YLW, PNK, // K
		PNK, YLW, YLW, YLW, YLW, // J
		PNK, PNK, PNK, PNK,      // I
		VIO, WHI, RED,           // H
		PNK, BLU, ORY, BLU       // Y
	},
};
