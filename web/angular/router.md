#### events
- NavigationStart
- RoutesRecognized
- RouteConfigLoadStart
- RouteConfigLoadEnd
- NavigationEnd
- NavigationCancel
- NavigationError

#### guards
- CanActivate：to mediate navigation to a route
- CanActivateChild：to mediate navigation to a child route
- CanDeactivate：to mediate navigation away from the current route
- Resolve：to perform route data retrieval before route activation
- CanLoad：to mediate navigation to a feature module loaded asynchronously
