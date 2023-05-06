import { naiveui, tailwindcss } from "./config";

export default defineNuxtConfig({
  ssr: false,

  app: {
    head: {
      title: "Battery Energy Monitor",
      htmlAttrs: {
        lang: "en",
      },
    },
  },

  modules: ["@bg-dev/nuxt-naiveui", "@nuxtjs/tailwindcss"],

  naiveui,
  tailwindcss,
});
