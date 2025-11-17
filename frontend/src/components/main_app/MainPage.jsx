import {AppSidebar, AppSidebarInsertPage} from "@/components/main_app/AppSidebar.jsx";
import {SidebarProvider} from "@/components/ui/sidebar.jsx";
import {Routes, Route} from "react-router-dom";
import {DatabaseSearch} from "@/components/main_app/DatabaseSearch.jsx";
import {DeviceConnections} from "@/components/main_app/DeviceConnections.jsx";
import {Database, Unplug, Hand, Joystick} from "lucide-react";

const sidebarContent = [
    {
        label: "Setup",
        items: [
            {
                title: "Database Search",
                url: "Setup/DatabaseSearch",
                icon: <Database />,
                component: <DatabaseSearch/>
            },
            {
                title: "Device Connections",
                url: "Setup/DeviceConnections",
                icon: <Unplug />,
                component: <DeviceConnections/>,
            },
        ],
    },
    {
        label: "Connections",
        items: [
            {
                title: "Hand 1",
                url: "#",
                icon: <Hand />,
                subItems: [
                    {
                        title: "Hydraulics",
                        url: "#all",
                    },
                    {
                        title: "Angles",
                        url: "#unread",
                    },
                ],
            },
            {
                title: "Hand 1 Controller",
                url: "#",
                icon: <Joystick />,
                subItems: [
                ],
            },
        ],
    },
]

export function MainPage({}) {

    return (
        <SidebarProvider>
            {/* THE SIDEBAR ON THE LEFT */}
            <AppSidebar sidebarContent={sidebarContent} />

            {/* THE PAGES ON THE RIGHT */}
            <Routes>
                {/* DEFAULT ROUTE */}
                <Route
                    path="/"
                    element={
                        <AppSidebarInsertPage
                            component={<DatabaseSearch />}
                            url={"Setup/DatabaseSearch"}
                        />
                    }
                />

                {/* DYNAMIC ROUTES FROM sidebarContent */}
                {sidebarContent.map((group) =>
                    group.items
                        .filter((item) => item.component) // Only include items with a component
                        .map((item) => (
                            <Route
                                key={item.url}
                                path={item.url}
                                element={
                                    <AppSidebarInsertPage
                                        component={item.component}
                                        url={item.url}
                                    />
                                }
                            />
                        ))
                )}

            </Routes>
        </SidebarProvider>
    )
}





