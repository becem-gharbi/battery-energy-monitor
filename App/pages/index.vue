<template>
    <div class="page-center p-4">
        <DataSelect v-if="!settings" class="w-full" />

        <div v-else class="w-full">
            <n-card size="small">
                <n-page-header title="Sessions">
                    <template #avatar>
                        <NaiveIcon name="ph:lightning" />
                    </template>

                    <template #extra>
                        <div class="flex gap-2 flex-wrap">
                            <n-select v-model:value="currentSessionSelect" :options="sessionsSelect" class="w-min" />

                            <n-button @click="settingsActive = true">
                                <template #icon>
                                    <NaiveIcon name="ph:gear" />
                                </template>
                            </n-button>

                            <ColorModeToggler />
                        </div>
                    </template>

                    <MeterEnergy :measurements="measurements"></MeterEnergy>

                </n-page-header>
            </n-card>

            <n-card size="small" class="mt-4">
                <ChartMeasurements :measurements="measurements" class="m-3" />
            </n-card>

            <n-drawer v-model:show="settingsActive" :width="380" placement="left">
                <n-drawer-content closable>
                    <template #header>
                        <div class="flex items-center gap-2">
                            <NaiveIcon name="ph:gear" />
                            Settings
                        </div>

                    </template>
                    <FormSettings />
                </n-drawer-content>
            </n-drawer>
        </div>
    </div>
</template>

<script setup lang="ts">
import type { SelectOption } from "naive-ui"

const sessions = useState<Session[]>("sessions")
const settings = useState<Settings>("settings")
const currentSession = ref<Session>()
const measurements = ref<Measurements>()
const settingsActive = ref(false)
const currentSessionSelect = ref()

const sessionsSelect = computed<SelectOption[]>(() => sessions.value.map(el => ({
    label: el.name.split(".")[0],
    value: el.lastModified
})))

watch(sessions, () => {
    if (sessions.value?.length > 0) {
        currentSession.value = sessions.value[0]
        currentSessionSelect.value = currentSession.value?.lastModified
    }
})

watch(currentSessionSelect, () => {
    currentSession.value = sessions.value.find(el => el.lastModified === currentSessionSelect.value)
})

watch(currentSession, async () => {
    if (currentSession.value) {
        measurements.value = await transformSession(currentSession.value)
    }
})
</script>

<style>
.page-center {
    min-height: 100vh;
    min-height: 100dvh;
    width: 100%;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
}
</style>