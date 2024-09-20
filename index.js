const express = require("express");
const axios = require("axios");
const dotenv = require("dotenv");
const app = express();
dotenv.config();
const port = process.env.PORT;

const blynkAuthToken = process.env.BLYNK_AUTH_TOKEN;

app.get("/turnon", async (req, res) => {
  try {
    const url = `http://blynk.cloud/external/api/update?token=${blynkAuthToken}&V1=1`;
    const response = await axios.get(url);
    res.send("Triggered ON via Blynk V1");
  } catch (error) {
    res.status(500).send("Error triggering ON");
  }
});

app.listen(port, () => {
  console.log(`Server running on http://localhost:${port}`);
});
