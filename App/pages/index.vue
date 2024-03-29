<template>
      <div class="page-center p-4">
        <DataSelect v-if="!settings" />

        <div v-else class="w-full">
            <n-card size="small" title="Sessions" segmented hoverable>

                <template #header-extra>
                    <div class="flex items-center gap-2 flex-wrap">
                        <n-select v-model:value="currentSessionSelect" :options="sessionsSelect" class="w-44" />

                        <n-button @click="settingsActive = true" secondary>
                            <template #icon>
                                <NaiveIcon name="ph:gear" />
                            </template>
                        </n-button>

                        <NaiveColorModeSwitch :text="false" secondary />
                    </div>
                </template>


                <StatsEnergy :measurements="measurements"></StatsEnergy>
            </n-card>

            <n-card size="small" class="mt-4 p-0" hoverable>
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
    value: el.name
})))

watch(sessions, () => {
    if (sessions.value?.length > 0) {
        currentSession.value = sessions.value[0]
        currentSessionSelect.value = currentSession.value?.name
    }
})

watch(currentSessionSelect, () => {
    currentSession.value = sessions.value.find(el => el.name === currentSessionSelect.value)
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
    justify-content: center;
}
</style>