<template>
    <n-button @click="toggleColorMode" tag="span" :focusable="false">
        <NaiveIcon v-if="colorModePreference === 'dark'" name="ph:moon"></NaiveIcon>
        <NaiveIcon v-else-if="colorModePreference === 'light'" name="ph:sun"></NaiveIcon>
        <NaiveIcon v-else-if="colorModePreference === 'system'" name="ph:monitor"></NaiveIcon>
    </n-button>
</template>

<script setup>
const { colorModePreference } = useNaiveColorMode()

function toggleColorMode() {
    switch (colorModePreference.value) {
        case ("light"):
            colorModePreference.value = "dark"
            break
        case ("dark"):
            colorModePreference.value = "system"
            break
        case ("system"):
            colorModePreference.value = "light";
            break
    }
}
</script>